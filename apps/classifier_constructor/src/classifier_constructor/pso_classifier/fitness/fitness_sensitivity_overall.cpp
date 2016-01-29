//
// Created by jakub on 1/25/16.
//

#include <language/language.h>
#include <classifier_constructor/pso_classifier/fitness/fitness_sensitivity_overall.h>
#include <classifier_quality.h>
#include <pso/particle_decoder.h>

FitnessSensitivityOverall::FitnessSensitivityOverall(
        ParticleShPtr_ConstVectorShPtr particles,
        const ParticleDecoder *particleDecoder,
        std::vector<Language *> *nativeLanguages,
        std::vector<Language *> *foreignLanguages) :
            FitnessUpdater(particles, particleDecoder){
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;
}

FitnessSensitivityOverall::~FitnessSensitivityOverall() {

}

double FitnessSensitivityOverall::fitnessValue(const Particle &p) {
    DFA* dfa = (DFA*)this->particleDecoder->decodeCurrent(p);

    double sensitivity = quality::calculateSensitivityOverall(nativeLanguages,
                                                              foreignLanguages,
                                                              dfa);
    delete dfa;

    return sensitivity;
}
