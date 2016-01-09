//
// Created by jakub on 12/29/15.
//

#include "pso_t.h"

#include <logger/log.h>
#include <pso/fitness_updater.h>
#include <pso/neighbourhood_updater.h>
#include <pso/particle_updater.h>

namespace pso {
//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

PSO_T::PSO_T(int maxIterations,
                FitnessUpdater* fitnessUpdater,
                NeighbourhoodUpdater* neighUpdater,
                ParticleUpdater* particleUpdater,
                unsigned int threadCount,
                unsigned int swarmSize):
        maxIterations(maxIterations),
        fitnessUpdater(fitnessUpdater),
        neighUpdater(neighUpdater),
        particleUpdater(particleUpdater),
        threadCount(threadCount),
        swarmSize(swarmSize){

}

PSO_T::~PSO_T() {
    delete fitnessUpdater;
    delete neighUpdater;
    delete particleUpdater;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void PSO_T::start() {
    threading::ThreadPool threadPool(threadCount);

    // Create structure for thread arguments
    thread_argv* targs = new thread_argv[threadCount];

    // Pointer to initial function
    void* (*fun_ptr)(void*);
    fun_ptr = &startParallelPSO;

    int curr_iter = 0;
    bool do_work = true;

    int reminder = this->swarmSize % threadPool.size();
    int sub_count = this->swarmSize / threadPool.size();

    // Initialize the structure with data
    for(unsigned int i = 0; i < threadCount; i++){

        int start = i * sub_count;
        int finish = start + sub_count - 1;
        if (i == threadCount - 1)
            finish += reminder;

        targs[i].startIndex = start;
        targs[i].finishIndex = finish;

        targs[i].tid = i;
        targs[i].pso = this;
        targs[i].curr_iter = &curr_iter;
        targs[i].do_work = &do_work;

        targs[i].threadPool = &threadPool;

        threadPool.createThread(fun_ptr, (&targs[i]));
    }

    threadPool.joinAll();
}
const Particle_T* PSO_T::getBestParticle() const{
    return bestParticle.get();
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

bool PSO_T::hasConvereged(const int* iter){
    return (*iter >= this->maxIterations);
}

void *startParallelPSO(void *argv) {
    thread_argv *targs = (thread_argv *) argv;

    PSO_T* pso = targs->pso;
    bool* do_work = targs->do_work;
    int* curr_iter = targs->curr_iter;
    unsigned int tid = targs->tid;
    threading::ThreadPool *threadPool = targs->threadPool;

    threadPool->lockAll();

    logger::log("[TID]: ", tid, " indices: ",
                targs->startIndex, ", ", targs->finishIndex);

    threadPool->unlockAll();

    threadPool->synchronizeAll();

    if (tid == threading::T_BOSS) {
        *do_work = true;
        *curr_iter = 0;
    }

    threadPool->synchronizeAll();

    while (*do_work) {

        threadPool->synchronizeAll();

        pso->fitnessUpdater->update(targs->startIndex,
                                    targs->finishIndex);

        threadPool->synchronizeAll();

        if (tid == threading::T_BOSS) {
            pso->neighUpdater->update();
        }

        threadPool->synchronizeAll();

        pso->particleUpdater->update(targs->startIndex,
                                     targs->finishIndex);

        threadPool->synchronizeAll();

        if (tid == threading::T_BOSS) {
            *do_work = !pso->hasConvereged(curr_iter);
            *curr_iter += 1;
        }

        threadPool->synchronizeAll();
    }
    return NULL;
}
}