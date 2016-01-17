//
// Created by jakub on 1/7/16.
//

#include <pso_classifier/dfa_particle_decoder.h>
#include <pso/entities/particle.h>
#include <pso/pso_common.h>
#include <vector>
#include <automata/transition/transition_function.h>
#include <automata/dfa.h>

using namespace pso;

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

DFAParticleDecoder::DFAParticleDecoder(int numberOfStates,
                                        int numberOfSymbols,
                                        double encodingDelta) {
    this->numberOfStates = numberOfStates;
    this->numberOfSymbols = numberOfSymbols;

    this->encodingDelta = encodingDelta;
}

DFAParticleDecoder::~DFAParticleDecoder() {

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

PSOObject* DFAParticleDecoder::decodeCurrent(const Particle &p) const {
    const PointDouble& position = p.getPosition();

    return this->decodePosition(position);
}

PSOObject* DFAParticleDecoder::decodePBest(const Particle &p) const {
    const PointDouble& position = p.getPbest();

    return this->decodePosition(position);
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

PSOObject* DFAParticleDecoder::decodePosition(
                    const PointDouble position) const {
    int size = position.size();

    std::vector<int> decodedParticle(size);

    for (int i = 0; i < size; i++) {
        int encodedValue;
        double delta;

        encodedValue = (int)(position)[i];
        delta = position[i] - encodedValue;
        if (delta >= encodingDelta)
            encodedValue++;

        // We enumerate from 0
        decodedParticle[i] = encodedValue - 1;
    }

    TransitionFunction* tf = new TransitionFunction(this->numberOfStates,
                                                    this->numberOfSymbols,
                                                    decodedParticle);
    DFA* dfa = new DFA(tf);

    return dfa;
}