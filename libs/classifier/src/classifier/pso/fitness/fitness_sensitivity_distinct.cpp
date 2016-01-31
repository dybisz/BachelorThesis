//
// Created by jakub on 1/26/16.
//


#include <classifier_quality.h>
#include <pso/particle_decoder.h>
#include <classifier/pso/fitness/fitness_sensitivity_distinct.h>

FitnessSensitivityDistinct::FitnessSensitivityDistinct(
        ParticleShPtr_ConstVectorShPtr particles,
        const ParticleDecoder *particleDecoder,
        std::vector<Language *> *nativeLanguages,
        std::vector<Language *> *foreignLanguages) :
            FitnessUpdater(particles, particleDecoder){
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;
}

FitnessSensitivityDistinct::~FitnessSensitivityDistinct() {

}

double FitnessSensitivityDistinct::fitnessValue(const Particle &p) {
    DFA* dfa = (DFA*)this->particleDecoder->decodeCurrent(p);

    double sensitivity = quality::calculateSensitivityDistinct(nativeLanguages,
                                                               foreignLanguages,
                                                               dfa);
    delete dfa;

    return sensitivity;
}
