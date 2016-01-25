//
// Created by jakub on 1/7/16.
//

#include <pso_classifier_tests/pso_classifier_common_test.h>

#include <gtest/gtest.h>

#include <classifier_constructor/pso_classifier/dfa_particle_decoder.h>

#include <language/word.h>
#include <language/language.h>
#include <classifier_constructor/pso_classifier/fitness/fitness_accuracy_distinct.h>

using namespace pso;

TEST(DFAFitnessUpdater,
     SingleLanguageWithWord_EndingStateNotEqualToCorresponding_Fitness0) {
    unsigned int nativeCount = 1;

    unsigned int alphabetSize = 2;

    std::vector<int> word_entries{0,1,1};
    Word w(word_entries);

    std::vector<Language*> *nativeLanguages = new std::vector<Language*>;
    std::vector<Language*> *foreignLanguages = new std::vector<Language*>;
    Alphabet alphabet(alphabetSize);

    for(unsigned int i = 0; i < nativeCount; i++){
        std::vector<State*> states;
        states.push_back(new State(0));

        Language* language = new Language(alphabet);
        language->addWord(&w);
        language->setStates(states);

        nativeLanguages->push_back(language);
    }

    Particle* particle = new Particle(createParticle_s4_r2());

    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;
    double encodingDelta = 0.5;

    ParticleDecoder* decoder =
            new DFAParticleDecoder (stateCount, symbolCount,
                                encodingDelta);

    ParticleShPtr particle_ShPtr(particle);
    std::vector<ParticleShPtr>* particles =
            new std::vector<ParticleShPtr>();
    particles->push_back(particle_ShPtr);
    ParticleShPtr_ConstVectorShPtr particles_ShPtr(particles);

    FitnessUpdater* fitnessUpdater =
            new FitnessAccuracyDistinct(particles_ShPtr,decoder,
                                        nativeLanguages,foreignLanguages);

    fitnessUpdater->update(0,0);

    double expectedFitness = 0.0f;
    double actualFintess = particle->getFitness();

    EXPECT_EQ(expectedFitness, actualFintess);

    delete fitnessUpdater;
}


TEST(DFAFitnessUpdater,
     SingleLanguageWithWord_EndingStateEqualToCorresponding_Fitness1) {
    unsigned int nativeCount = 1;

    unsigned int alphabetSize = 2;

    std::vector<int> word_entries{0,1,1};
    Word w(word_entries);

    std::vector<Language*> *nativeLanguages = new std::vector<Language*>;
    std::vector<Language*> *foreignLanguages = new std::vector<Language*>;
    Alphabet alphabet(alphabetSize);

    for(unsigned int i = 0; i < nativeCount; i++){
        std::vector<State*> states;
        states.push_back(new State(2));

        Language* language = new Language(alphabet);
        language->addWord(&w);
        language->setStates(states);

        nativeLanguages->push_back(language);
    }

    Particle* particle = new Particle(createParticle_s4_r2());

    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;
    double encodingDelta = 0.5;

    ParticleDecoder* decoder =
            new DFAParticleDecoder (stateCount, symbolCount,
                                    encodingDelta);

    ParticleShPtr particle_ShPtr(particle);
    std::vector<ParticleShPtr>* particles =
            new std::vector<ParticleShPtr>();
    particles->push_back(particle_ShPtr);
    ParticleShPtr_ConstVectorShPtr particles_ShPtr(particles);

    FitnessUpdater* fitnessUpdater =
            new FitnessAccuracyDistinct(particles_ShPtr,decoder,
                                        nativeLanguages,foreignLanguages);

    fitnessUpdater->update(0,0);

    double expectedFitness = 1.0f;
    double actualFintess = particle->getFitness();

    EXPECT_EQ(expectedFitness, actualFintess);

    delete fitnessUpdater;
}