//
// Created by jakub on 1/26/16.
//

#include <classifier_constructor/pso_classifier/fitness/fitness_precision_distinct.h>
#include <pso/particle_decoder.h>
#include <classifier_quality.h>

FitnessPrecisionDistinct::FitnessPrecisionDistinct(
        ParticleShPtr_ConstVectorShPtr particles,
        const ParticleDecoder *particleDecoder,
        std::vector<Language *> *nativeLanguages,
        std::vector<Language *> *foreignLanguages) :
            FitnessUpdater(particles, particleDecoder){
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;
}

FitnessPrecisionDistinct::~FitnessPrecisionDistinct() {

}

double FitnessPrecisionDistinct::fitnessValue(const Particle &p) {
    DFA* dfa = (DFA*)this->particleDecoder->decodeCurrent(p);

    double precision = quality::calculatePrecisionDistinct(nativeLanguages,
                                                          foreignLanguages,
                                                          dfa);
    delete dfa;

    return precision;
}
