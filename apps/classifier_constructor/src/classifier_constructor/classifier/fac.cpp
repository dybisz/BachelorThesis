//
// Created by jakub on 1/20/16.
//

#include "classifier_constructor/classifier/fac.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

FAC::FAC(DFA dfa, Correspondence correspondence)
        : dfa(dfa), correspondence(correspondence){

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const DFA &FAC::getDFA() const {
    return this->dfa;
}

const Correspondence& FAC::getCorrespondence() const {
    return this->correspondence;
}

const Label &FAC::classify(Word &word) const {
    int stateValue = dfa.compute(word);
    State state(stateValue);

    const vector<Label>& labels = correspondence.getLabels();
    for(unsigned int i = 0; i < labels.size(); i++){
        if(correspondence.isCorresponding(labels[i], state))
            return labels[i];
    }

    throw invalid_argument("No state correspondence");
}
