//
// Created by jakub on 1/7/16.
//

#ifndef BACHELOR_THESIS_DFA_PARTICLE_DECODER_H
#define BACHELOR_THESIS_DFA_PARTICLE_DECODER_H

#include <pso/particle_decoder_t.h>

using namespace pso;

class DFAParticleDecoder : public ParticleDecoder_T{
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    int numberOfStates;
    int numberOfSymbols;

    double encodingDelta;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    PSOObject* decodePosition(const PointDouble position) const;

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    DFAParticleDecoder(int numberOfStates,
                        int numberOfSymbols,
                        double encodingDelta);

    virtual ~DFAParticleDecoder();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    virtual PSOObject* decodeCurrent(const Particle_T &p) const override;

    virtual PSOObject* decodePBest(const Particle_T &p) const override;
};


#endif //BACHELOR_THESIS_DFA_PARTICLE_DECODER_H
