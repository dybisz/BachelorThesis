//
// Created by jakub on 12/29/15.
//

#include "particle_updater.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

using namespace pso;

ParticleUpdater::ParticleUpdater(
                ParticleShPtr_ConstVectorShPtr particles) {
    this->particles = particles;
}

ParticleUpdater::~ParticleUpdater() {

}