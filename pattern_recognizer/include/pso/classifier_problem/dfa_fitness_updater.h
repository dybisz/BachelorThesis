//
// Created by jakub on 1/7/16.
//

#ifndef BACHELOR_THESIS_CLASSIFIER_FITNESS_UPDATER_H
#define BACHELOR_THESIS_CLASSIFIER_FITNESS_UPDATER_H

#include <pso/pso_common.h>
#include <pso/fitness_updater.h>
#include <languages/language.h>
using namespace pso;

class DFAFitnessUpdater : public FitnessUpdater{
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

    virtual double fitnessValue(const Particle_T& p) override;

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    DFAFitnessUpdater(ParticleShPtr_ConstVectorShPtr particles,
                                const ParticleDecoder_T* particleDecoder,
                                std::vector<Language*>* nativeLanguages,
                                std::vector<Language*>* foreignLanguages);

    virtual ~DFAFitnessUpdater();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    virtual void update(int startIndex, int finishIndex) override;
};


#endif //BACHELOR_THESIS_CLASSIFIER_FITNESS_UPDATER_H
