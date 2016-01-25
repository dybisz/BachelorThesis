//
// Created by jakub on 1/20/16.
//

#include "classifier_constructor/classifier/cfac.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

CFAC::CFAC(std::vector<FAC> facClassifiers, int alphabetSize) {
    for(unsigned int i = 0; i < facClassifiers.size(); i++){
        this->facClassifiers.push_back(facClassifiers[i]);
    }

    this->alphabetSize = alphabetSize;
}


CFAC::~CFAC() {

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const std::vector<FAC> &CFAC::getClassifiers() const {
    return this->facClassifiers;
}

int CFAC::getAlphabetSize() const {
    return this->alphabetSize;
}

const Label &CFAC::classify(const Word &word) const {
    return Label(1);
}