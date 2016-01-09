//
// Created by jakub on 1/6/16.
//

#ifndef BACHELOR_THESIS_PARTICLE_DECODER_TEST_H
#define BACHELOR_THESIS_PARTICLE_DECODER_TEST_H


#include <pso/particle_decoder_t.h>
#include "pso_object_test.h"
/*
 * This class is used to test test the communication
 * between classes in the entire module.
 */
class ParticleDecoderTest : public pso::ParticleDecoder_T {

public:
    ParticleDecoderTest() {

    }

    virtual ~ParticleDecoderTest() {

    }

    virtual
    pso::PSOObject *decodeCurrent(const pso::Particle_T &p) const override {
        return new PSOObjectTest;
    }

    virtual
    pso::PSOObject *decodePBest(const pso::Particle_T &p) const override {
        return new PSOObjectTest;
    }
};


#endif //BACHELOR_THESIS_PARTICLE_DECODER_TEST_H
