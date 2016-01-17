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
    class ParticleDecoder;
    class ParticleFactory;
    class Particle;
    class PSOObject;
    class PSO;

    // ---------------------------------------------------
    typedef std::shared_ptr<PSO>
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
    typedef std::shared_ptr<ParticleDecoder>
            ParticleDecoderShPtr;
    // ---------------------------------------------------
    typedef std::shared_ptr<Particle>
            ParticleShPtr;

    typedef std::vector<std::shared_ptr<Particle>>
            ParticleShPtr_Vector;
    typedef const std::vector<std::shared_ptr<Particle>>
            ParticleShPtr_ConstVector;

    typedef std::shared_ptr<const std::vector <std::shared_ptr<Particle>>>
            ParticleShPtr_ConstVectorShPtr;

    typedef std::shared_ptr<std::vector <std::shared_ptr<Particle>>>
            ParticleShPtr_VectorShPtr;

    typedef std::shared_ptr<std::vector <std::shared_ptr<Particle>>>
            ParticleShPtr_VectorShPtr;

    // ---------------------------------------------------
}

#endif //BACHELOR_THESIS_PSO_COMMON_H
