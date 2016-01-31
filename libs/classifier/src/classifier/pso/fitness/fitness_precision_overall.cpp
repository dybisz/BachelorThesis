//
// Created by jakub on 1/25/16.
//

#include <language/language.h>

#include <classifier_quality.h>
#include <pso/particle_decoder.h>
#include <classifier/pso/fitness/fitness_precision_overall.h>

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

FitnessPrecisionOverall::FitnessPrecisionOverall(
        ParticleShPtr_ConstVectorShPtr particles,
        const ParticleDecoder *particleDecoder,
        std::vector<Language *> *nativeLanguages,
        std::vector<Language *> *foreignLanguages) :
            FitnessUpdater(particles, particleDecoder){
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;
}

FitnessPrecisionOverall::~FitnessPrecisionOverall() {

}

//-----------------------------------------------------------//
//  PROTECTED METHODS
//-----------------------------------------------------------//

double FitnessPrecisionOverall::fitnessValue(const Particle &p) {
    DFA* dfa = (DFA*)this->particleDecoder->decodeCurrent(p);

    double precision = quality::calculatePrecisionOverall(nativeLanguages,
                                                          foreignLanguages,
                                                          dfa);
    delete dfa;

    return precision;
}
