//
// Created by jakub on 1/26/16.
//

#ifndef BACHELOR_THESIS_FITNESS_PRECISION_DISTINCT_H
#define BACHELOR_THESIS_FITNESS_PRECISION_DISTINCT_H

#include <pso/fitness_updater.h>
#include <language/language.h>

using namespace pso;

class FitnessPrecisionDistinct : public FitnessUpdater{
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

    FitnessPrecisionDistinct(ParticleShPtr_ConstVectorShPtr particles,
                             const ParticleDecoder* particleDecoder,
                             std::vector<Language*>* nativeLanguages,
                             std::vector<Language*>* foreignLanguages);

    ~FitnessPrecisionDistinct();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//
};


#endif //BACHELOR_THESIS_FITNESS_PRECISION_DISTINCT_H
