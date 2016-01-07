//
// Created by jakub on 12/29/15.
//

#include "particle_t.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

using namespace pso;

Particle_T::Particle_T(double posIntervalMin, double posIntervalMax,
                            double velIntervalMin, double velIntervalMax,
                            double maxVelocity,
                            Point<double> position, Point<double> velocity) :
                posIntervalMin(posIntervalMin), posIntervalMax(posIntervalMin),
                velIntervalMin(velIntervalMin), velIntervalMax(velIntervalMin),
                maxVelocity(maxVelocity),
                position(position), velocity(velocity),
                pbest(position), lbest(position){
}

Particle_T::~Particle_T() {

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

//-----------------------------------------------------------//
//  GETTERS
//-----------------------------------------------------------//

double Particle_T::getPosIntervalMin() const {
    return posIntervalMin;
}

double Particle_T::getPosIntervalMax() const {
    return posIntervalMax;
}

double Particle_T::getVelIntervalMin() const {
    return velIntervalMin;
}

double Particle_T::getVelIntervalMax() const {
    return velIntervalMax;
}

double Particle_T::getMaxVelocity() const {
    return maxVelocity;
}

const PointDouble& Particle_T::getPosition() const {
    return position;
}

const PointDouble& Particle_T::getVelocity() const {
    return velocity;
}

const PointDouble& Particle_T::getPbest() const {
    return pbest;
}

const PointDouble& Particle_T::getLbest() const {
    return lbest;
}

double Particle_T::getFitness() const {
    return fitness;
}

double Particle_T::getBestFitness() const {
    return bestFitness;
}

//-----------------------------------------------------------//
//  SETTERS
//-----------------------------------------------------------//

void Particle_T::setFitness(double fitness) {
    this->fitness = fitness;
}

void Particle_T::setBestFitness(double fitness) {
    this->bestFitness = fitness;
}

void Particle_T::setPosition(PointDouble position) {
    this->position = position;
}

void Particle_T::setVelocity(PointDouble velocity) {
    this->velocity = velocity;
}

void Particle_T::setPbest(PointDouble pbest) {
    this->pbest = pbest;
}

void Particle_T::setLbest(PointDouble lbest) {
    this->lbest= lbest;
}
