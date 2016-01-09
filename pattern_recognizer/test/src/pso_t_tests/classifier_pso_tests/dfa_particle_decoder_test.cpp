//
// Created by jakub on 1/7/16.
//

#include "dfa_particle_decoder_test.h"

#include <gtest/gtest.h>

#include <pso/entities/particle_t.h>
#include <pso/classifier_problem/dfa_particle_decoder.h>
#include <automata/dfa.h>
#include <pso_t_test.h>

using namespace pso;



TEST(DFAParticleDecoder, ParticleDecodedIntoDFA_MediumWord_ProperComputeState) {
    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;
    double encodingDelta = 0.5;

    DFAParticleDecoder decoder(stateCount, symbolCount,
                               encodingDelta);

    Particle_T p = createParticle_s4_r2();

    DFA* dfa = (DFA*)decoder.decodeCurrent(p);

    std::vector<int> word_entries{0,1,1};
    Word w(word_entries);

    int expectedState = 2;
    int actualState = dfa->compute(w);

    EXPECT_EQ(expectedState, actualState);

    delete dfa;
}

TEST(DFAParticleDecoder, ParticleDecodedIntoDFA_SmallWord_ProperComputeState) {
    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;
    double encodingDelta = 0.5;

    DFAParticleDecoder decoder(stateCount, symbolCount,
                               encodingDelta);

    Particle_T p = createParticle_s4_r2();

    DFA* dfa = (DFA*)decoder.decodeCurrent(p);

    std::vector<int> word_entries2{0};
    Word w2(word_entries2);

    int expectedState = 1;
    int actualState = dfa->compute(w2);

    EXPECT_EQ(expectedState, actualState);

    delete dfa;
}


TEST(DFAParticleDecoder,
     ParticlePBestDecodedIntoDFA_MediumWord_ProperComputeState) {
    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;
    double encodingDelta = 0.5;

    DFAParticleDecoder decoder(stateCount, symbolCount,
                               encodingDelta);

    Particle_T p = createParticle_s4_r2();

    DFA* dfa = (DFA*)decoder.decodePBest(p);

    std::vector<int> word_entries{0,1,1};
    Word w(word_entries);

    int expectedState = 2;
    int actualState = dfa->compute(w);

    EXPECT_EQ(expectedState, actualState);

    delete dfa;
}

TEST(DFAParticleDecoder,
     ParticlePBestDecodedIntoDFA_SmallWord_ProperComputeState) {
    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;
    double encodingDelta = 0.5;

    DFAParticleDecoder decoder(stateCount, symbolCount,
                               encodingDelta);

    Particle_T p = createParticle_s4_r2();

    DFA* dfa = (DFA*)decoder.decodePBest(p);

    std::vector<int> word_entries2{0};
    Word w2(word_entries2);

    int expectedState = 1;
    int actualState = dfa->compute(w2);

    EXPECT_EQ(expectedState, actualState);

    delete dfa;
}