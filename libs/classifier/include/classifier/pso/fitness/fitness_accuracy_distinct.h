//
// Created by jakub on 1/7/16.
//

#ifndef BACHELOR_THESIS_CLASSIFIER_FITNESS_UPDATER_H
#define BACHELOR_THESIS_CLASSIFIER_FITNESS_UPDATER_H

#include <pso/pso_common.h>
#include <pso/fitness_updater.h>
#include <language/language.h>

using namespace pso;

class FitnessAccuracyDistinct : public FitnessUpdater{
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    std::vector<Language*>* nativeLanguages;
    std::vector<Language*>* foreignLanguages;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

protected:
    //-----------------------------------------------------------//
    //  PROTECTED METHODS
    //-----------------------------------------------------------//

    virtual double fitnessValue(const Particle& p) override;

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    FitnessAccuracyDistinct(ParticleShPtr_ConstVectorShPtr particles,
                            const ParticleDecoder* particleDecoder,
                            std::vector<Language*>* nativeLanguages,
                            std::vector<Language*>* foreignLanguages);

    virtual ~FitnessAccuracyDistinct();

};


#endif //BACHELOR_THESIS_CLASSIFIER_FITNESS_UPDATER_H
