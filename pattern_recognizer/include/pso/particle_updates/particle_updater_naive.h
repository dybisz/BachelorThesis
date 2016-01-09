//
// Created by kuba on 1/8/16.
//

#ifndef BACHELOR_THESIS_PARTICLE_UPDATER_NAIVE_H
#define BACHELOR_THESIS_PARTICLE_UPDATER_NAIVE_H

#include <pso/particle_updater.h>
#include <pso/pso_common.h>

namespace pso {

class ParticleUpdaterNaive : public ParticleUpdater {

    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    ParticleUpdaterNaive(ParticleShPtr_ConstVectorShPtr particles);

    virtual ~ParticleUpdaterNaive();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    virtual void update(int startIndex, int finishIndex) override;
};

}

#endif //BACHELOR_THESIS_PARTICLE_UPDATER_NAIVE_H
