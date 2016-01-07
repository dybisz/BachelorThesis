//
// Created by jakub on 12/29/15.
//

#ifndef BACHELOR_THESIS_PARTICLE_UPDATER_H
#define BACHELOR_THESIS_PARTICLE_UPDATER_H

#include "pso_common.h"

namespace pso {

/*
 * Pure Abstract class used to provide interface for Particle Update.
 *
 * Has ownership over:
 *      - Raw pointer to ParticleDecoder
 *      - Shared pointer to ParticleShPtr_ConstVectorShPtr
 */
class ParticleUpdater {
protected:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    ParticleShPtr_ConstVectorShPtr particles;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    ParticleUpdater(ParticleShPtr_ConstVectorShPtr particles);

    virtual ~ParticleUpdater();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Updates the particles from startIndex to finishIndex
     */
    virtual void update(int startIndex, int finishIndex) = 0;
};
}

#endif //BACHELOR_THESIS_PARTICLE_UPDATER_H
