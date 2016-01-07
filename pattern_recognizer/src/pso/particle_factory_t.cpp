//
// Created by jakub on 12/29/15.
//

#include "particle_factory_t.h"

using namespace pso;

ParticleFactory_T::ParticleFactory_T(int swarmSize, int particleDimension,
                                          double posIntervalMin,
                                          double posIntervalMax,
                                          double velIntervalMin,
                                          double velIntervalMax,
                                          double maxVelocity) :
                swarmSize(swarmSize), particleDimension(particleDimension),
                posIntervalMin(posIntervalMin), posIntervalMax(posIntervalMax),
                velIntervalMin(velIntervalMin), velIntervalMax(velIntervalMax),
                maxVelocity(maxVelocity) {

}

ParticleFactory_T::~ParticleFactory_T() {

}


ParticleShPtr_ConstVectorShPtr ParticleFactory_T::createUnifromParticles() {
    ParticleShPtr_ConstVectorShPtr particles =
            std::make_shared<ParticleShPtr_ConstVector>();

    return particles;
}
