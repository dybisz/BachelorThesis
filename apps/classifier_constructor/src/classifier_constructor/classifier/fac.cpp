//
// Created by jakub on 1/20/16.
//

#include "classifier_constructor/classifier/fac.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

FAC::FAC() {

}

FAC::~FAC() {

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const std::vector<FACClassifier> &FAC::getClassifiers() const {
    return this->facClassifiers;
}

const Label &FAC::classify(const Word &word) const {
    return Label(1);
}