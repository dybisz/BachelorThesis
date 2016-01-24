//
// Created by jakub on 1/20/16.
//

#include "classifier_constructor/classifier/fac.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//


FAC::FAC(DFA dfa)
        : dfa(dfa){

}

FAC::FAC(DFA dfa,
         std::vector<Correspondence>
                                                stateCorrespondence)
        : dfa(dfa), correspondenceVector(stateCorrespondence){

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//


void FAC::addCorrespondence(
        Correspondence stateCorrespondence) {
    this->correspondenceVector.push_back(stateCorrespondence);
}

const DFA &FAC::getDFA() const {
    return this->dfa;
}

const std::vector<Correspondence>&
FAC::getCorrespondence() const {
    return this->correspondenceVector;
}

const Label &FAC::classify(const Word &word) const {
    return Label(0);
}
