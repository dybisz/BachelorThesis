//
// Created by jakub on 12/29/15.
//

#ifndef BACHELOR_THESIS_PARTICLE_FACTORY_T_H
#define BACHELOR_THESIS_PARTICLE_FACTORY_T_H

#include "pso_common.h"
namespace pso {

class ParticleFactory_T {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    int swarmSize;

    int particleDimension;

    double posIntervalMin;
    double posIntervalMax;

    double velIntervalMin;
    double velIntervalMax;

    double maxVelocity;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:

    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    ParticleFactory_T(int swarmSize, int particleDimension,
                      double posIntervalMin, double posIntervalMax,
                      double velIntervalMin, double velIntervalMax,
                      double maxVelocity);

    ~ParticleFactory_T();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    ParticleShPtr_ConstVectorShPtr createUnifromParticles();
};
}

#endif //BACHELOR_THESIS_PARTICLE_FACTORY_T_H
