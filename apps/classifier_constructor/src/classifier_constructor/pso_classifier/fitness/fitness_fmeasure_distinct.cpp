//
// Created by jakub on 1/26/16.
//

#include <classifier_constructor/pso_classifier/fitness/fitness_fmeasure_distinct.h>
#include <classifier_quality.h>
#include <pso/particle_decoder.h>

FitnessFmeasureDistinct::FitnessFmeasureDistinct(
        ParticleShPtr_ConstVectorShPtr particles,
        const ParticleDecoder *particleDecoder,
        std::vector<Language *> *nativeLanguages,
        std::vector<Language *> *foreignLanguages) :
            FitnessUpdater(particles, particleDecoder){
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;
}

FitnessFmeasureDistinct::~FitnessFmeasureDistinct() {

}

double FitnessFmeasureDistinct::fitnessValue(const Particle &p) {
    DFA* dfa = (DFA*)this->particleDecoder->decodeCurrent(p);

    double fmeasure = quality::calculateFMeasureDistinct(nativeLanguages,
                                                         foreignLanguages,
                                                         dfa);
    delete dfa;

    return fmeasure;
}
