//
// Created by jakub on 12/29/15.
//

#ifndef BACHELOR_THESIS_PSO_T_H
#define BACHELOR_THESIS_PSO_T_H

#include "pso_common.h"
#include <threading/thread_pool.h>

namespace pso{
    extern void* startParallelPSO(void* argv);

    struct thread_argv{
        unsigned int tid;
        PSO_T* pso;
        int* curr_iter;
        bool* do_work;

        int startIndex;
        int finishIndex;

        threading::ThreadPool* threadPool;
    };


/*
 * Encapsulates all the parts of PSO algorithm.
 *
 * Has ownership over:
 *      - Raw pointer to
 *          - FitnessUpdater
 *          - NeighbourhoodUpdater
 *          - ParticleUpdater
 */
class PSO_T {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    int maxIterations;

    FitnessUpdater* fitnessUpdater;
    NeighbourhoodUpdater* neighUpdater;
    ParticleUpdater* particleUpdater;

    ParticleShPtr bestParticle;

    unsigned int threadCount;

    unsigned int swarmSize;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    void compute();

    bool hasConvereged(const int* iter);

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//;

    PSO_T(int maxIterations,
            FitnessUpdater* fitnessUpdater,
            NeighbourhoodUpdater* neighUpdater,
            ParticleUpdater* particleUpdater,
            unsigned int threadCount,
            unsigned int swarmSize);

    ~PSO_T();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Starts the computations
     */
    void start();

    /*
     * Returns the best particle found by the computations
     */
    const Particle_T* getBestParticle() const;

    friend void* startParallelPSO(void* argv);
};
}

#endif //BACHELOR_THESIS_PSO_T_H
