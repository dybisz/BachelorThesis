//
// Created by jakub on 12/22/15.
//

#include <classifier/classifier.h>


using namespace pso;

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Classifier::Classifier(pso::PSO * pso,
                       std::vector<Language*>* nativeLanguages,
                       std::vector<Language*>* foreignLanguages){
    this->_nativeLanguages = nativeLanguages;
    this->_foreignLanguages = foreignLanguages;

    this->pso = pso;
    this->classifierDFA = NULL;
}

Classifier::~Classifier() {
    for (unsigned int i = 0; i < _nativeLanguages->size(); i++)
        delete (*_nativeLanguages)[i];
    for (unsigned int i = 0; i < _foreignLanguages->size(); i++)
        delete (*_foreignLanguages)[i];

    delete _nativeLanguages;
    delete _foreignLanguages;

    if(pso != NULL)
        delete pso;
    if(classifierDFA != NULL){
        delete classifierDFA;
    }

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const DFA &Classifier::getClassiferDFA() const {
    return *classifierDFA;
}

void Classifier::runClassification() {
    pso->start();

    classifierDFA = (DFA*)pso->getBestPSOObject();
};
