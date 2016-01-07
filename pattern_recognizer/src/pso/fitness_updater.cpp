//
// Created by jakub on 12/29/15.
//

#include "fitness_updater.h"
#include "pso/particle_decoder_t.h"

using namespace pso;

FitnessUpdater::FitnessUpdater(ParticleShPtr_ConstVectorShPtr particles,
                                const ParticleDecoder_T* particleDecoder){
    this->particleDecoder = particleDecoder;
    this->particles = particles;
}

FitnessUpdater::~FitnessUpdater(){
    delete particleDecoder;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const ParticleDecoder_T& FitnessUpdater::getParticleDecoder() const {
    return *particleDecoder;
}

const ParticleShPtr_Vector& FitnessUpdater::getParticles() const {
    return *(particles.get());
}
