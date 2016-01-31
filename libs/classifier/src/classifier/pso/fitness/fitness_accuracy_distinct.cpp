//
// Created by jakub on 1/7/16.
//

#include <pso/particle_decoder.h>
#include <automata/dfa.h>
#include <classifier_quality.h>
#include <classifier/pso/fitness/fitness_accuracy_distinct.h>

using namespace pso;

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

FitnessAccuracyDistinct::FitnessAccuracyDistinct(
                                ParticleShPtr_ConstVectorShPtr particles,
                                const ParticleDecoder* particleDecoder,
                                std::vector<Language*>* nativeLanguages,
                                std::vector<Language*>* foreignLanguages) :
                FitnessUpdater(particles, particleDecoder){
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;
}

FitnessAccuracyDistinct::~FitnessAccuracyDistinct() {

}

//-----------------------------------------------------------//
//  PROTECTED METHODS
//-----------------------------------------------------------//

double FitnessAccuracyDistinct::fitnessValue(const Particle& p){
    DFA* dfa = (DFA*)this->particleDecoder->decodeCurrent(p);

    double accuracy = quality::calculateAccuracyDistinct(nativeLanguages,
                                                         foreignLanguages, dfa);

    delete dfa;

    return accuracy;
}