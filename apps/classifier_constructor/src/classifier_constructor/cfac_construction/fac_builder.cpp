//
// Created by jakub on 1/24/16.
//

#include "classifier_constructor/cfac_construction/fac_builder.h"

#include <pso/pso.h>

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

FACBuilder::FACBuilder(Correspondence correspondence,
                       PSO* pso) {
    this->correspondence = correspondence;

    this->pso = pso;

    this->classifier = NULL;
}

FACBuilder::~FACBuilder() {
    if(classifier != NULL){
        delete classifier;
    }
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//


void FACBuilder::build() {
    pso->start();

    const DFA* dfa = (DFA*)pso->getBestPSOObject();

    this->classifier = new FAC(*dfa, correspondence);
}

const FAC &FACBuilder::getClassifier() {
    if(classifier == NULL){
        throw invalid_argument("Can not acces Classifier before build");
    }
    return *classifier;
}
