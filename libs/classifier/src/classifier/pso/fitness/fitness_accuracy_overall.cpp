//
// Created by jakub on 1/25/16.
//

#include <classifier_quality.h>
#include <classifier/pso/fitness/fitness_accuracy_overall.h>
#include <pso/particle_decoder.h>

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

FitnessAccuracyOverall::FitnessAccuracyOverall(
        ParticleShPtr_ConstVectorShPtr particles,
        const ParticleDecoder *particleDecoder,
        std::vector<Language *> *nativeLanguages,
        std::vector<Language *> *foreignLanguages)
        : FitnessUpdater(particles, particleDecoder) {
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;
}

FitnessAccuracyOverall::~FitnessAccuracyOverall() {

}

//-----------------------------------------------------------//
//  PROTECTED METHODS
//-----------------------------------------------------------//

double FitnessAccuracyOverall::fitnessValue(const Particle &p) {
    DFA* dfa = (DFA*)this->particleDecoder->decodeCurrent(p);

    double accuracy = quality::calculateAccuracyOverall(nativeLanguages,
                                                        foreignLanguages,
                                                        dfa);
    delete dfa;

    return accuracy;
}
