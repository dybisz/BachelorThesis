//
// Created by jakub on 1/6/16.
//

#ifndef BACHELOR_THESIS_FITNESS_UPDATER_TEST_H
#define BACHELOR_THESIS_FITNESS_UPDATER_TEST_H


#include <pso/fitness_updater.h>
#include <pso/entities/particle_t.h>
#include <pso/particle_decoder_t.h>

using namespace pso;

class FitnessUpdaterTest : public FitnessUpdater{
protected:
    virtual double fitnessValue(const Particle_T& p) override{

    }
public:

    FitnessUpdaterTest(ParticleShPtr_ConstVectorShPtr particles,
                       ParticleDecoder_T* particleDecoder) :
            FitnessUpdater(particles, particleDecoder){

    }

    virtual void update(int startIndex, int finishIndex) override {

    }

};


#endif //BACHELOR_THESIS_FITNESS_UPDATER_TEST_H
