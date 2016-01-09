//
// Created by jakub on 12/30/15.
//

#ifndef BACHELOR_THESIS_PSO_COMMON_H
#define BACHELOR_THESIS_PSO_COMMON_H

#include <math/point.h>
#include <memory>

/*
 * Header used to store common typedefs and forward declaration of PSO module
 */
namespace pso
{
    class FitnessUpdater;
    class NeighbourhoodUpdater;
    class ParticleUpdater;
    class ParticleDecoder_T;
    class ParticleFactory_T;
    class Particle_T;
    class PSOObject;
    class PSO_T;

    // ---------------------------------------------------
    typedef std::shared_ptr<PSO_T>
            PSOShPtr;
    // ---------------------------------------------------
    typedef std::shared_ptr<FitnessUpdater>
            FitnessUpdaterShPtr;

    typedef std::shared_ptr<NeighbourhoodUpdater>
            NeighbourhoodUpdaterShPtr;

    typedef std::shared_ptr<ParticleUpdater>
            ParticleUpdaterShPtr;
    // ---------------------------------------------------
    typedef std::shared_ptr<PSOObject>
            PSOObjectShPtr;
    // ---------------------------------------------------
    typedef Point<double>
            PointDouble;

    typedef std::shared_ptr<Point<double>>
            PointDoubleShPtr;
    // ---------------------------------------------------
    typedef std::shared_ptr<ParticleDecoder_T>
            ParticleDecoderShPtr;
    // ---------------------------------------------------
    typedef std::shared_ptr<Particle_T>
            ParticleShPtr;

    typedef std::vector<std::shared_ptr<Particle_T>>
            ParticleShPtr_Vector;
    typedef const std::vector<std::shared_ptr<Particle_T>>
            ParticleShPtr_ConstVector;

    typedef std::shared_ptr<const std::vector <std::shared_ptr<Particle_T>>>
            ParticleShPtr_ConstVectorShPtr;

    typedef std::shared_ptr<std::vector <std::shared_ptr<Particle_T>>>
            ParticleShPtr_VectorShPtr;

    typedef std::shared_ptr<std::vector <std::shared_ptr<Particle_T>>>
            ParticleShPtr_VectorShPtr;

    // ---------------------------------------------------
}

#endif //BACHELOR_THESIS_PSO_COMMON_H
