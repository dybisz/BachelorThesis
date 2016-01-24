//
// Created by jakub on 1/20/16.
//

#include "classifier_constructor/classifier/cfac.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

CFAC::CFAC() {

}

CFAC::~CFAC() {

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const std::vector<FAC> &CFAC::getClassifiers() const {
    return this->facClassifiers;
}

const Label &CFAC::classify(const Word &word) const {
    return Label(1);
}