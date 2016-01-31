//
// Created by jakub on 1/20/16.
//

#include <vector>
#include <pso/pso.h>
#include <classifier/pso/pso_factory.h>
#include <classifier/pso/fitness/fitness_accuracy_distinct.h>
#include <classifier/pso/fitness/fitness_accuracy_overall.h>
#include <classifier/pso/fitness/fitness_precision_overall.h>
#include <classifier/pso/fitness/fitness_sensitivity_overall.h>
#include <classifier/pso/fitness/fitness_fmeasure_overall.h>
#include <classifier/pso/fitness/fitness_precision_distinct.h>
#include <classifier/pso/fitness/fitness_sensitivity_distinct.h>
#include <classifier/pso/fitness/fitness_fmeasure_distinct.h>

using namespace pso;

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

PSOFactory::PSOFactory(std::vector<Language *> *nativeLanguages,
                       std::vector<Language *> *foreignLanguages,
                       int statesPerNative, int statesPerForeign,
                       int alphabetSize,
                       int swarmSize, int maximumIterations, int threadCount,
                       double maxVelocity,
                       double encodingDelta, double uppderBoundError,
                       double learningFactor, double particleVelocityWeight,
                       FitnessType fitnessType) {
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;

    this->statesPerNative = statesPerNative;
    this->statesPerForeign = statesPerForeign;

    this->alphabetSize = alphabetSize;

    this->swarmSize = swarmSize;
    this->maximumIterations = maximumIterations;

    this->threadCount = threadCount;

    this->maxVelocity = maxVelocity;
    this->encodingDelta = encodingDelta;
    this->uppderBoundError = uppderBoundError;
    this->learningFactor = learningFactor;
    this->particleVelocityWeight = particleVelocityWeight;

    this->fitnessType = fitnessType;
}

PSOFactory::PSOFactory(int swarmSize, int maximumIterations, int threadCount,
                       double maxVelocity, double encodingDelta,
                       double uppderBoundError, double learningFactor,
                       double particleVelocityWeight) {
    this->swarmSize = swarmSize;
    this->maximumIterations = maximumIterations;

    this->threadCount = threadCount;

    this->maxVelocity = maxVelocity;
    this->encodingDelta = encodingDelta;
    this->uppderBoundError = uppderBoundError;
    this->learningFactor = learningFactor;
    this->particleVelocityWeight = particleVelocityWeight;
}

PSOFactory::~PSOFactory() {

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

PSO* PSOFactory::createPSO(){
    int numberOfStates = calculateNumberOfStates();
    int particleDimension = calculateParticleDimension();
    double posIntervalMin = calculatePosIntervalMin();
    double posIntervalMax = calculatePosIntervalMax();

    ParticleFactory particleFactory
            = createParticleFactory(swarmSize, particleDimension,
                                    posIntervalMin, posIntervalMax,
                                    -numberOfStates, numberOfStates,
                                    maxVelocity );

    ParticleShPtr_ConstVectorShPtr particles =
            particleFactory.createUnifromParticles();
    ParticleDecoder * particleDecoder
            = createParticleDecoder(numberOfStates, alphabetSize,
                                    encodingDelta);

    FitnessUpdater* fitnessUpdater
            = createFitnessUpdater(particles, particleDecoder);
    int numberOfInformants = 3;
    NeighbourhoodUpdater* neighbourhoodUpdater
            = createNeighbourhoodUpdater(particles, numberOfInformants);

    int numberOfTries = 1;
    ParticleUpdater* particleUpdater
            = createPaticleUpdater(particles, learningFactor,
                                   particleVelocityWeight, numberOfTries);

    PSO * pso = new PSO(particles,
                        fitnessUpdater,
                        neighbourhoodUpdater,
                        particleUpdater,
                        maximumIterations, threadCount);
    return pso;
}

PSO *PSOFactory::createPSO(std::vector<Language *> *nativeLanguages,
                           std::vector<Language *> *foreignLanguages,
                           int statesPerNative, int statesPerForeign,
                           int alphabetSize) {
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;

    this->statesPerNative = statesPerNative;
    this->statesPerForeign = statesPerForeign;

    this->alphabetSize = alphabetSize;

    this->createPSO();
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//


double PSOFactory::calculatePosIntervalMin() {
    double posIntervalMin = encodingDelta;
    return posIntervalMin;
}

double PSOFactory::calculatePosIntervalMax() {
    int numberOfStates = calculateNumberOfStates();
    double posIntervalMax = (numberOfStates + encodingDelta) - uppderBoundError;

    return posIntervalMax;
}


int PSOFactory::calculateParticleDimension() {
    int numberOfStates = calculateNumberOfStates();

    int particleDimension = numberOfStates * alphabetSize;

    return particleDimension;
}

int PSOFactory::calculateNumberOfStates() {
    int nativeSize = nativeLanguages->size();
    int numberOfStates = nativeSize * statesPerNative + statesPerForeign;

    return numberOfStates;
}


ParticleFactory PSOFactory::createParticleFactory(int swarmSize,
                                      int particleDimension,
                                      double posIntervalMin,
                                      double posIntervalMax,
                                      double velIntervalMin,
                                      double velIntervalMax,
                                      double maxVelocity ){

    ParticleFactory particleFactory(
            swarmSize, particleDimension,
            posIntervalMin, posIntervalMax,
            velIntervalMin, velIntervalMax,
            maxVelocity
    );

    return particleFactory;
}

ParticleDecoder* PSOFactory::createParticleDecoder(int numberOfStates,
                                        int numberOfSymbols,
                                        double encodingDelta){

    ParticleDecoder * particleDecoder = new DFAParticleDecoder(
            numberOfStates, numberOfSymbols,
            encodingDelta
    );

    return particleDecoder;
}

NeighbourhoodUpdater* PSOFactory::createNeighbourhoodUpdater(
        ParticleShPtr_ConstVectorShPtr particles,
        int numberOfParticlesToInform ){

    NeighbourhoodUpdater* neighbourhoodUpdater = new pso::NBStarTopology(
            particles, numberOfParticlesToInform
    );

    return neighbourhoodUpdater;
}

FitnessUpdater* PSOFactory::createFitnessUpdater(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder * particleDecoder){

    FitnessUpdater* fitnessUpdater;
    switch(fitnessType){
        case FitnessType::FITNESS_ACCURACY_DISTINCT:
            fitnessUpdater = createFitnessAccuracyDistinct(particles,
                                                           particleDecoder);
            break;
        case FitnessType::FITNESS_PRECISION_DISTINCT:
            fitnessUpdater = createFitnessPrecisionDistinct(particles,
                                                           particleDecoder);
            break;
        case FitnessType::FITNESS_SENSITIVITY_DISTINCT:
            fitnessUpdater = createFitnessSensitivityDistinct(particles,
                                                              particleDecoder);
            break;
        case FitnessType::FITNESS_FMEASURE_DISTINCT:
            fitnessUpdater = createFitnessFmeasureDistinct(particles,
                                                           particleDecoder);
            break;
        case FitnessType::FITNESS_ACCURACY_OVERALL:
            fitnessUpdater = createFitnessAccuracyOverall(particles,
                                                           particleDecoder);
            break;
        case FitnessType::FITNESS_PRECISION_OVERALL:
            fitnessUpdater = createFitnessPrecisionOverall(particles,
                                                           particleDecoder);
            break;
        case FitnessType::FITNESS_SENSITIVITY_OVERALL:
            fitnessUpdater = createFitnessSensitivityOverall(particles,
                                                             particleDecoder);
            break;
        case FitnessType::FITNESS_FMEASURE_OVERALL:
            fitnessUpdater = createFitnessFmeasureOverall(particles,
                                                          particleDecoder);
            break;
        default:
            throw invalid_argument("No such FitnessType");
    }
    return fitnessUpdater;
}

ParticleUpdater* PSOFactory::createPaticleUpdater(
        ParticleShPtr_ConstVectorShPtr particles,
        double learningFactor, double velocityWeight,
        int timesToAttemptPointGenerationWithinHyperSphere){

    ParticleUpdater* particleUpdater = new ParticleUpdaterSpherical(
            particles,
            learningFactor,velocityWeight,
            timesToAttemptPointGenerationWithinHyperSphere
    );

    return particleUpdater;
}

FitnessUpdater *PSOFactory::createFitnessAccuracyDistinct(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder *particleDecoder) {
    FitnessUpdater* fitnessUpdater = new FitnessAccuracyDistinct(
            particles, particleDecoder,
            nativeLanguages, foreignLanguages
    );

    return fitnessUpdater;
}

FitnessUpdater *PSOFactory::createFitnessAccuracyOverall(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder *particleDecoder) {
    FitnessUpdater* fitnessUpdater = new FitnessAccuracyOverall(
            particles, particleDecoder,
            nativeLanguages, foreignLanguages
    );
    return fitnessUpdater;
}

FitnessUpdater *PSOFactory::createFitnessPrecisionOverall(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder *particleDecoder) {
    FitnessUpdater* fitnessUpdater = new FitnessPrecisionOverall(
            particles, particleDecoder,
            nativeLanguages, foreignLanguages
    );
    return fitnessUpdater;
}

FitnessUpdater *PSOFactory::createFitnessSensitivityOverall(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder *particleDecoder) {
    FitnessUpdater* fitnessUpdater = new FitnessSensitivityOverall(
            particles, particleDecoder,
            nativeLanguages, foreignLanguages
    );
    return fitnessUpdater;
}

FitnessUpdater *PSOFactory::createFitnessFmeasureOverall(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder *particleDecoder) {
    FitnessUpdater* fitnessUpdater = new FitnessFmeasureOverall(
            particles, particleDecoder,
            nativeLanguages, foreignLanguages
    );
    return fitnessUpdater;
}

FitnessUpdater *PSOFactory::createFitnessPrecisionDistinct(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder *particleDecoder) {
    FitnessUpdater* fitnessUpdater = new FitnessPrecisionDistinct(
            particles, particleDecoder,
            nativeLanguages, foreignLanguages
    );
    return fitnessUpdater;
}

FitnessUpdater *PSOFactory::createFitnessSensitivityDistinct(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder *particleDecoder) {
    FitnessUpdater* fitnessUpdater = new FitnessSensitivityDistinct(
            particles, particleDecoder,
            nativeLanguages, foreignLanguages
    );
    return fitnessUpdater;
}

FitnessUpdater *PSOFactory::createFitnessFmeasureDistinct(
        ParticleShPtr_ConstVectorShPtr particles,
        ParticleDecoder *particleDecoder) {
    FitnessUpdater* fitnessUpdater = new FitnessFmeasureDistinct(
            particles, particleDecoder,
            nativeLanguages, foreignLanguages
    );
    return fitnessUpdater;
}
