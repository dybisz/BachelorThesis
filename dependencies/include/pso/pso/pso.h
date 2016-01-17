//
// Created by jakub on 12/29/15.
//

#ifndef BACHELOR_THESIS_PSO_T_H
#define BACHELOR_THESIS_PSO_T_H

#include <pso/entities/particle.h>
#include <pso/pso_common.h>

#include <threading/thread_pool.h>

namespace pso{
    extern void* startParallelPSO(void* argv);

    struct thread_argv{
        unsigned int tid;
        PSO * pso;
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
class PSO {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    ParticleShPtr_ConstVectorShPtr particles;

    FitnessUpdater* fitnessUpdater;
    NeighbourhoodUpdater* neighUpdater;
    ParticleUpdater* particleUpdater;

    ParticleShPtr bestParticle;

    Particle globalBestParticle;

    int maxIterations;

    unsigned int threadCount;

    unsigned int swarmSize;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    void compute();

    void resetParticles();

    /*
     * Checks whether the PSO should converge
     */
    bool hasConvereged(const int* iter);

    /*
     * Updates the best particle among all particles.
     * Returns true if new particle has became best
     */
    bool updateBestParticle();

    void printInfo(double fitnessUpdateTime,
                    double neighbourhoodUpdateTime,
                    double particleUpdateTime,
                    double overallTime,
                    double averageTimeOfIteration,
                    double ETA,
                    int currentIteration,
                    int& numberOfLinesToReset);

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//;

    PSO(ParticleShPtr_ConstVectorShPtr particles,
          FitnessUpdater* fitnessUpdater,
          NeighbourhoodUpdater* neighUpdater,
          ParticleUpdater* particleUpdater,
          int maxIterations,
          unsigned int threadCount);

    ~PSO();

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
    const Particle * getBestParticle() const;

    /*
     * Decodes best particle and returns the PSOObject
     * representing this particle
     */
    const PSOObject* getBestPSOObject() const;

    const ParticleDecoder & getDecoder() const;

    //-----------------------------------------------------------//
    //  FRIEND METHODS
    //-----------------------------------------------------------//

    friend void* startParallelPSO(void* argv);
};
}

#endif //BACHELOR_THESIS_PSO_T_H