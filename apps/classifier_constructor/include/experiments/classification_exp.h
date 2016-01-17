//
// Created by jakub on 12/22/15.
//

#ifndef BACHELOR_THESIS_CLASSIFICATION_EXP_H
#define BACHELOR_THESIS_CLASSIFICATION_EXP_H

#include <patterns/pattern.h>
#include <language/language.h>
#include <vector>
#include <pso/particle_updater.h>
#include <pso_classifier/dfa_fitness_updater.h>

namespace experiments
{
    void runPSOBasedClassification();

    namespace classification
    {
        pso::PSO * createPSO(pso::ParticleShPtr_ConstVectorShPtr particles,
                              pso::FitnessUpdater* fitnessUpdater,
                              pso::NeighbourhoodUpdater* neighUpdater,
                              pso::ParticleUpdater* particleUpdater,
                              int maxIterations, int threadCount);

        pso::ParticleFactory createParticleFactory(int swarmSize,
                                                     int particleDimension,
                                                     double posIntervalMin,
                                                     double posIntervalMax,
                                                     double velIntervalMin,
                                                     double velIntervalMax,
                                                     double maxVelocity );

        pso::ParticleDecoder * createParticleDecoder(int numberOfStates,
                                                      int numberOfSymbols,
                                                      double encodingDelta);

        pso::NeighbourhoodUpdater* createNeighbourhoodUpdater(
                pso::ParticleShPtr_ConstVectorShPtr particles,
                int numberOfParticlesToInform );

        pso::FitnessUpdater* createFitnessUpdater(
                pso::ParticleShPtr_ConstVectorShPtr particles,
                pso::ParticleDecoder * particleDecoder,
                std::vector<Language*>* nativeLanguages,
                std::vector<Language*>* foreignLanguages);


        pso::ParticleUpdater* createPaticleUpdater(
                pso::ParticleShPtr_ConstVectorShPtr particles,
                double learningFactor, double velocityWeight,
                int timesToAttemptPointGenerationWithinHyperSphere);

        void printLoadedPatternsInfo(std::vector<Pattern*>* patterns,
                                     std::string headerInfo);

        void printTransformedLanguagesInfo(std::vector<Language*>* languages,
                                           std::string headerInfo);
    }
}
#endif //BACHELOR_THESIS_CLASSIFICATION_EXP_H