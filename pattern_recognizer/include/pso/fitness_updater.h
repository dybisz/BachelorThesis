//
// Created by jakub on 12/29/15.
//

#ifndef BACHELOR_THESIS_FITNESS_UPDATER_H
#define BACHELOR_THESIS_FITNESS_UPDATER_H

#include <particle_t.h>
#include "pso_common.h"

namespace pso {
/*
 * Pure Abstract class used to provide interface for Fitness update
 *
 * Has ownership over:
 *      - Raw pointer to ParticleDecoder
 *      - Shared pointer to ParticleShPtr_ConstVectorShPtr
 */
class FitnessUpdater {
protected:

    //-----------------------------------------------------------//
    //  PROTECTED FIELDS
    //-----------------------------------------------------------//

    const ParticleDecoder_T* particleDecoder;

    ParticleShPtr_ConstVectorShPtr particles;

    //-----------------------------------------------------------//
    //  PROTECTED METHODS
    //-----------------------------------------------------------//

    /*
     * Computes fitness value of a single particle
     */
    virtual double fitnessValue(const Particle_T& p) = 0;

public:

    //-----------------------------------------------------------//
    //  CONSTRUCTOR
    //-----------------------------------------------------------//

    FitnessUpdater(ParticleShPtr_ConstVectorShPtr particles,
                   const ParticleDecoder_T* particleDecoder);

    virtual ~FitnessUpdater();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    const ParticleDecoder_T& getParticleDecoder() const;

    const ParticleShPtr_Vector& getParticles() const;

    /*
     * Updates the particles from startIndex to finishIndex
     */
    virtual void update(int startIndex, int finishIndex) = 0;
};
}

#endif //BACHELOR_THESIS_FITNESS_UPDATER_H