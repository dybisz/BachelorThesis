//
// Created by jakub on 1/25/16.
//

#include <classifier_quality.h>
#include <pso/particle_decoder.h>
#include <classifier/pso/fitness/fitness_fmeasure_overall.h>

FitnessFmeasureOverall::FitnessFmeasureOverall(
        ParticleShPtr_ConstVectorShPtr particles,
        const ParticleDecoder *particleDecoder,
        std::vector<Language *> *nativeLanguages,
        std::vector<Language *> *foreignLanguages) :
            FitnessUpdater(particles, particleDecoder){
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;
}

FitnessFmeasureOverall::~FitnessFmeasureOverall() {

}

double FitnessFmeasureOverall::fitnessValue(const Particle &p) {
    DFA* dfa = (DFA*)this->particleDecoder->decodeCurrent(p);

    double fmeasure = quality::calculateFMeasureOverall(nativeLanguages,
                                                        foreignLanguages,
                                                        dfa);
    delete dfa;

    return fmeasure;
}
