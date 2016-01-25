//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_PSOFACTORY_H
#define BACHELOR_THESIS_PSOFACTORY_H

#include <language/language.h>
#include <pso/particle_factory.h>
#include <classifier_constructor/pso_classifier/dfa_particle_decoder.h>
#include <pso/neighbourhood_updaters/nb_star_topology.h>
#include <pso/particle_updaters/particle_updater_spherical.h>

using namespace pso;

/*
 * Used to choose between different FitnessUpdaters
 */
enum FitnessType{
    FITNESS_ACCURACY_DISTINCT       = 0,
    FITNESS_ACCURACY_OVERALL        = 1,
    FITNESS_PRECISION_OVERALL       = 2,
    FITNESS_SENSITIVITY_OVERALL     = 3,
    FITNESS_FMEASURE_OVERALL        = 4
};

/*
 * Creates PSO instance.
 * All the allocated memory should be deleted manually
 */
class PSOFactory {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    std::vector<Language *>* nativeLanguages;
    std::vector<Language *>* foreignLanguages;

    int statesPerNative;
    int statesPerForeign;
    int alphabetSize;

    int swarmSize;
    int maximumIterations;

    int threadCount;

    double maxVelocity;
    double encodingDelta;
    double uppderBoundError;
    double learningFactor;
    double particleVelocityWeight;

    FitnessType fitnessType;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    double calculatePosIntervalMin();
    double calculatePosIntervalMax();

    int calculateParticleDimension();

    int calculateNumberOfStates();

    ParticleFactory createParticleFactory(
            int swarmSize, int particleDimension,
            double posIntervalMin, double posIntervalMax,
            double velIntervalMin, double velIntervalMax,
            double maxVelocity);

    ParticleDecoder * createParticleDecoder(
            int numberOfStates, int numberOfSymbols,
            double encodingDelta);

    NeighbourhoodUpdater* createNeighbourhoodUpdater(
            ParticleShPtr_ConstVectorShPtr particles,
            int numberOfParticlesToInform );

    FitnessUpdater* createFitnessUpdater(
            ParticleShPtr_ConstVectorShPtr particles,
            ParticleDecoder * particleDecoder);

    FitnessUpdater* createFitnessAccuracyDistinct(
            ParticleShPtr_ConstVectorShPtr particles,
            ParticleDecoder * particleDecoder);

    FitnessUpdater* createFitnessAccuracyOverall(
            ParticleShPtr_ConstVectorShPtr particles,
            ParticleDecoder * particleDecoder);

    FitnessUpdater* createFitnessPrecisionOverall(
            ParticleShPtr_ConstVectorShPtr particles,
            ParticleDecoder * particleDecoder);

    FitnessUpdater* createFitnessSensitivityOverall(
            ParticleShPtr_ConstVectorShPtr particles,
            ParticleDecoder * particleDecoder);

    FitnessUpdater* createFitnessFmeasureOverall(
            ParticleShPtr_ConstVectorShPtr particles,
            ParticleDecoder * particleDecoder);

    ParticleUpdater* createPaticleUpdater(
            ParticleShPtr_ConstVectorShPtr particles,
            double learningFactor, double velocityWeight,
            int timesToAttemptPointGenerationWithinHyperSphere);

public:

    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    PSOFactory(std::vector<Language *> *nativeLanguages,
               std::vector<Language *> *foreignLanguages,
               int statesPerNative, int statesPerForeign,
               int alphabetSize,
               int swarmSize, int maximumIterations, int threadCount,
               double maxVelocity,
               double encodingDelta, double uppderBoundError,
               double learningFactor, double particleVelocityWeight,
               FitnessType fitnessType);

    PSOFactory(int swarmSize, int maximumIterations, int threadCount,
               double maxVelocity,
               double encodingDelta, double uppderBoundError,
               double learningFactor, double particleVelocityWeight);

    ~PSOFactory();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    PSO* createPSO();

    PSO* createPSO(std::vector<Language *> *nativeLanguages,
                   std::vector<Language *> *foreignLanguages,
                   int statesPerNative, int statesPerForeign,
                   int alphabetSize);
};


#endif //BACHELOR_THESIS_PSOFACTORY_H
