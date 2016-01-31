//
// Created by jakub on 1/26/16.
//

#include <pso/particle_decoder.h>
#include <classifier_quality.h>
#include <classifier/pso/fitness/fitness_precision_distinct.h>

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
