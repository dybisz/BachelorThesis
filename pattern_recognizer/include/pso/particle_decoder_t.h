//
// Created by jakub on 12/29/15.
//

#ifndef BACHELOR_THESIS_PARTICLE_DECODER_T_H
#define BACHELOR_THESIS_PARTICLE_DECODER_T_H

#include "pso_common.h"

namespace pso {
class ParticleDecoder_T {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTOR
    //-----------------------------------------------------------//

    ParticleDecoder_T();

    virtual ~ParticleDecoder_T();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Decodes particle's current position
     */
    virtual PSOObject* decodeCurrent(const Particle_T& p) const = 0;

    /*
     * Decodes particles's personal best position
     */
    virtual PSOObject* decodePBest(const Particle_T& p) const = 0;
};
}

#endif //BACHELOR_THESIS_PARTICLE_DECODER_T_H
