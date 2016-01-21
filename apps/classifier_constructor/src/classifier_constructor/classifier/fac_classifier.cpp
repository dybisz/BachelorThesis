//
// Created by jakub on 1/20/16.
//

#include "classifier_constructor/classifier/fac_classifier.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//


FACClassifier::FACClassifier(DFA dfa)
        : dfa(dfa){

}

FACClassifier::FACClassifier(DFA dfa,
                             std::vector<Correspondence>
                                                stateCorrespondence)
        : dfa(dfa), stateCorrespondenceVector(stateCorrespondence){

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//


void FACClassifier::addStateCorrespondence(
        Correspondence stateCorrespondence) {
    this->stateCorrespondenceVector.push_back(stateCorrespondence);
}

const DFA &FACClassifier::getDFA() const {
    return this->dfa;
}

const std::vector<Correspondence>&
FACClassifier::getStateCorrespondence() const {
    return this->stateCorrespondenceVector;
}

const Label &FACClassifier::classify(const Word &word) const {
    return Label(0);
}
