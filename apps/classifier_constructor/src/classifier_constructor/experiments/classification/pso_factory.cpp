//
// Created by jakub on 1/20/16.
//

#include <vector>
#include "classifier_constructor/experiments/classification/pso_factory.h"
#include <pso/pso.h>

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
                       double learningFactor, double particleVelocityWeight) {

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
    FitnessUpdater* fitnessUpdater = new DFAFitnessUpdater(
            particles, particleDecoder,
            nativeLanguages, foreignLanguages
    );

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