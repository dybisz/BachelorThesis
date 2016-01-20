//
// Created by jakub on 1/20/16.
//

#include "classifier_constructor/classifier/state_correspondence.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

StateCorrespondence::StateCorrespondence(State state)
        : state(state){
}

StateCorrespondence::StateCorrespondence(State state,
                                         std::vector<Label> labels)
        : state(state){
    this->labels = labels;
}


//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//


void StateCorrespondence::addLabel(Label label) {
    this->labels.push_back(label);
}

const std::vector<Label> &StateCorrespondence::getLabels() {
    return this->labels;
}

bool StateCorrespondence::isCorresponding(const Label &label) {
    for(unsigned int i = 0; i < labels.size(); i++){
        if (label == labels[i])
            return true;
    }
    return false;
}
