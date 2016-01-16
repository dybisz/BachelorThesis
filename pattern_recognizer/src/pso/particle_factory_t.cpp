//
// Created by jakub on 12/29/15.
//

#include <utils.h>
#include "particle_factory_t.h"
#include <pso/entities/particle_t.h>
#include <sstream>
#include <logger/log.h>

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

    std::stringstream ss;
    ss << "Creating Particles" << std::endl;
    ss << "Count:          " << swarmSize << std::endl;
    ss << "Dimensions:     " << particleDimension << std::endl;

    ss << "posIntervalMin: " << posIntervalMin << std::endl;
    ss << "posIntervalMax: " << posIntervalMax << std::endl;

    ss << "velIntervalMin: " << velIntervalMin << std::endl;
    ss << "velIntervalMax: " << velIntervalMax << std::endl;

    ss << "maxVelocity:    " << maxVelocity << std::endl;

    logger::log(ss.str());

    ParticleShPtr_Vector* particles = new ParticleShPtr_Vector(swarmSize);

    for(unsigned int i = 0; i < swarmSize; i++){
        Point<double> position(particleDimension);
        Point<double> velocity(particleDimension);

        for(unsigned int j = 0; j < particleDimension; j++){
            position[j] = utils::generateRandomNumber(posIntervalMin,
                                                      posIntervalMax);
            velocity[j] = utils::generateRandomNumber(velIntervalMin,
                                                      velIntervalMax);
        }

        ParticleShPtr particle = std::make_shared<Particle_T>(
                posIntervalMin, posIntervalMax,
                velIntervalMin, velIntervalMax,
                maxVelocity,
                position, velocity
        );
        (*particles)[i] = (particle);
    }

    ParticleShPtr_ConstVectorShPtr particlesShPtr(particles);

    return particlesShPtr;
}
