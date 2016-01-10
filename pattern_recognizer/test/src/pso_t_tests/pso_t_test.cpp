//
// Created by jakub on 1/4/16.
//

#include <gtest/gtest.h>

#include <pso_t_test.h>
#include <logger/log.h>

using namespace pso;

Particle_T createParticle_s4_r2(){
    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;

    double posMin = 0.0f;
    double posMax = 5.0f;

    double velMin = 0.0f;
    double velMax = 5.0f;

    double maxVel = 1.0f;

    Point<double> pos(8);
    pos[0] = 2.0f;
    pos[1] = 3.0f;
    pos[2] = 3.0f;
    pos[3] = 4.0f;

    pos[4] = 4.0f;
    pos[5] = 3.0f;
    pos[6] = 3.0f;
    pos[7] = 4.0f;

    Point<double> vel(8);

    Particle_T p(posMin, posMax,
                 velMin, velMax,
                 maxVel,
                 pos, vel);
    return p;
}

PSO_T createPSOInstance(){
    int particleDimension = 10;

    double posIntervalMin = 0.0f;
    double posIntervalMax = 5.0f;

    double velIntervalMin = -5.0f;
    double velIntervalMax = 5.0f;

    double maxVelocity = 10.0f;

    int swarmSize = 50;

    int maxIterations = 2;

    unsigned int threadCount = 8;

    ParticleFactory_T particleFactory
            (
                    swarmSize, particleDimension,
                    posIntervalMin, posIntervalMax,
                    velIntervalMin, velIntervalMax,
                    maxVelocity
            );

    ParticleDecoder_T* particleDecoder = new ParticleDecoderTest();

    ParticleShPtr_ConstVectorShPtr particles =
            particleFactory.createUnifromParticles();

    FitnessUpdater* fitnessUpdater = new FitnessUpdaterTest
            (
                    particles, particleDecoder
            );

    NeighbourhoodUpdater* neighbourhoodUpdater = new NeighbourhoodUpdaterTest
            (
                    particles
            );
    ParticleUpdater* particleUpdater = new ParticleUpdaterTest
            (
                    particles
            );

    PSO_T pso(particles,
              fitnessUpdater,
              neighbourhoodUpdater,
              particleUpdater,
              maxIterations,
              threadCount);

    return pso;

}

TEST(PSO, GetBestParticleBeforeStart_Null) {
    PSO_T pso = createPSOInstance();

    const Particle_T* bestParticle = pso.getBestParticle();

    EXPECT_EQ(NULL, bestParticle);
}

TEST(PSO, Start) {
    PSO_T pso = createPSOInstance();

    pso.start();

    const Particle_T* bestParticle = pso.getBestParticle();

    //EXPECT_EQ(NULL, bestParticle);
}