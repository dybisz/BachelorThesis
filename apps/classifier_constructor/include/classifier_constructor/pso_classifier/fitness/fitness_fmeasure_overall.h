//
// Created by jakub on 1/25/16.
//

#ifndef BACHELOR_THESIS_FITNESS_FMEASURE_OVERALL_H
#define BACHELOR_THESIS_FITNESS_FMEASURE_OVERALL_H

#include <pso/fitness_updater.h>
#include <language/language.h>

using namespace pso;

class FitnessFmeasureOverall : public FitnessUpdater {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    std::vector<Language*>* nativeLanguages;
    std::vector<Language*>* foreignLanguages;

protected:
    //-----------------------------------------------------------//
    //  PROTECTED METHODS
    //-----------------------------------------------------------//

    virtual double fitnessValue(const Particle& p) override;

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    FitnessFmeasureOverall(ParticleShPtr_ConstVectorShPtr particles,
                           const ParticleDecoder* particleDecoder,
                           std::vector<Language*>* nativeLanguages,
                           std::vector<Language*>* foreignLanguages);

    ~FitnessFmeasureOverall();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//
};


#endif //BACHELOR_THESIS_FITNESS_FMEASURE_OVERALL_H
