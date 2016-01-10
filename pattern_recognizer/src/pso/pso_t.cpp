//
// Created by jakub on 12/29/15.
//

#include "pso_t.h"

#include <logger/log.h>
#include <pso/fitness_updater.h>
#include <pso/neighbourhood_updater.h>
#include <pso/particle_updater.h>
#include <pso/particle_decoder_t.h>
#include <clock.h>


using namespace std;

namespace pso {

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

PSO_T::PSO_T(ParticleShPtr_ConstVectorShPtr particles,
                FitnessUpdater* fitnessUpdater,
                NeighbourhoodUpdater* neighUpdater,
                ParticleUpdater* particleUpdater,
                int maxIterations,
                unsigned int threadCount):
        fitnessUpdater(fitnessUpdater),
        neighUpdater(neighUpdater),
        particleUpdater(particleUpdater),
        maxIterations(maxIterations),
        threadCount(threadCount){
    this->particles = particles;
    swarmSize = particles->size();
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

const PSOObject* PSO_T::getBestPSOObject() const {
    PSOObject* psoObject =
            this->getDecoder().decodePBest((*this->getBestParticle()));

    return psoObject;
}

const ParticleDecoder_T& PSO_T::getDecoder() const {
    return this->fitnessUpdater->getParticleDecoder();
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

bool PSO_T::hasConvereged(const int* iter){
    return (*iter >= this->maxIterations);
}

bool PSO_T::updateBestParticle(){
    bool hasChanged = false;

    bestParticle = (*particles)[0];
    for(unsigned int i = 0; i < swarmSize; i++){
        if((*particles)[i]->getBestFitness() > bestParticle->getBestFitness()){
            bestParticle = (*particles)[i];
            hasChanged = true;
        }
    }

    return hasChanged;
}

void PSO_T::printInfo(double fitnessUpdateTime,
                      double neighbourhoodUpdateTime,
                      double particleUpdateTime,
                      double overallTime,
                      double averageTimeOfIteration,
                      double ETA,
                      int currentIteration,
                      int& numberOfLinesToReset) {
    // Clean previous entry
    for (int i = 0; i < numberOfLinesToReset; i++) {
        cout << "\e[A\r";
    }

    numberOfLinesToReset = 0;
    string prefix = "          ";
    string prefixIcons = "               ";
    cout << endl;
    numberOfLinesToReset++;

    cout << prefixIcons << " ___  ___  ___" << endl;
    cout << prefixIcons << "| _ \\/ __|/ _ \\" << endl;
    cout << prefixIcons << "|  _/\\__ \\ (_) |" << endl;
    cout << prefixIcons << "|_|  |___/\\___/" << endl;
    cout << prefixIcons << "                    " << endl;
    numberOfLinesToReset += 5;

    cout << prefix << "[Iteration          ]: "
        << currentIteration << "/" << this->maxIterations << endl;
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Swarm Size         ]: "
    << this->swarmSize << endl;
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Overall Time       ]: "
    << overallTime << endl;
    numberOfLinesToReset++;

    cout << prefix << "[ETA Time           ]: "
    << ETA << endl;
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Avg Iter Time      ]: "
    << averageTimeOfIteration << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Last Fitness Time  ]: "
        << fitnessUpdateTime << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Last Neigh Time    ]: "
    << neighbourhoodUpdateTime << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Last Particle Time ]: "
    << particleUpdateTime << endl;
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    double bestFitness = 0;
    if (bestParticle != NULL) {
        bestFitness = bestParticle->getBestFitness();
    }
    cout << prefix << "[Best Fitness       ]: "
        << bestFitness << endl;
    numberOfLinesToReset++;

    cout << prefix << "" << endl;
    cout << prefix << "            .-. " << endl;
    cout << prefix << "           o   \\     .-." << endl;
    cout << prefix << "               .----.\'   \\" << endl;
    cout << prefix << "              .\'o)  / `.   o" << endl;
    cout << prefix << "             /         |" << endl;
    cout << prefix << "             \\_)       /-." << endl;
    cout << prefix << "              \'_.`    \\  \\" << endl;
    cout << prefix << "               `.      |  \\" << endl;
    cout << prefix << "               |       \\ |" << endl;
    cout << prefix << "           .--/`-.     / /" << endl;
    cout << prefix << "          .'.-/`-. `.  .\\|" << endl;
    cout << prefix << "         /.' /`._ `-    '-." << endl;
    cout << prefix << "    ____(|__/`-..`-   '-._ \\" << endl;
    cout << prefix << "   |`------.'-._ `      ||\\ \\" << endl;
    cout << prefix << "   || #   /-.   `   /   || \\|" << endl;
    cout << prefix << "   ||   #/   `--'  /  /_::_|)__" << endl;
    cout << prefix << "   `|____|-._.-`  /  ||`--------`" << endl;
    cout << prefix << "         \\-.___.` | / || #      |" << endl;
    cout << prefix << "          \\       | | ||   #  # |" << endl;
    cout << prefix << "          /`.___.'\\ |.`|________|" << endl;
    cout << prefix << "          | /`.__.'|'.`" << endl;
    cout << prefix << "        __/ \\    __/ \\" << endl;
    cout << prefix << "       /__.-.)  /__.-.)" << endl;
    cout << prefix << endl << endl;
    numberOfLinesToReset += 26;
}

//-----------------------------------------------------------//
//  FRIEND METHODS
//-----------------------------------------------------------//

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

    int numberOfLines = 0;

    double fitnessTime = 0;
    double neighTime = 0;
    double updateTime = 0;
    double overallTime = 0;
    double averageTimeOfIteration = 0;
    double ETA = 0;

    while (*do_work) {
        if (tid == threading::T_BOSS) {
            overallTime += fitnessTime + neighTime + updateTime;
            if(*curr_iter != 0)
                averageTimeOfIteration = overallTime / *curr_iter;
            ETA = averageTimeOfIteration * (pso->maxIterations - (*curr_iter));
            pso->printInfo(fitnessTime,
                           neighTime,
                           updateTime,
                           overallTime,
                           averageTimeOfIteration,
                           ETA,
                           *curr_iter, numberOfLines);
        }

        threadPool->synchronizeAll();

        if(tid == threading::T_BOSS)
            clk::startClock();
        pso->fitnessUpdater->update(targs->startIndex,
                                    targs->finishIndex);
        if(tid == threading::T_BOSS)
            fitnessTime = clk::stopClock();

        threadPool->synchronizeAll();
        bool doNeighUpdate = true;
        if(tid == threading::T_BOSS)
            doNeighUpdate = pso->updateBestParticle();

        threadPool->synchronizeAll();

        if (tid == threading::T_BOSS) {
            clk::startClock();
            if(doNeighUpdate)
                pso->neighUpdater->update();
            neighTime = clk::stopClock();
        }

        threadPool->synchronizeAll();

        if(tid == threading::T_BOSS)
            clk::startClock();
        pso->particleUpdater->update(targs->startIndex,
                                     targs->finishIndex);
        if(tid == threading::T_BOSS)
            updateTime = clk::stopClock();

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
