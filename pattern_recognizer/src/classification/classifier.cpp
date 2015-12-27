//
// Created by jakub on 12/22/15.
//

#include <language.h>
#include <settings/global_settings.h>
#include <logger/log.h>
#include <pso.h>
#include <drawer.h>
#include "classifier.h"


//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Classifier::Classifier(std::vector<Language*>* nativeLanguages,
                       std::vector<Language*>* foreignLanguages,
                       unsigned int statesPerNative,
                       unsigned int statesPerForeign,
                       unsigned int alphabetSize){
    this->_nativeLanguages = nativeLanguages;
    this->_foreignLanguages = foreignLanguages;

    _statesPerNative = statesPerNative;
    _statesPerForeign = statesPerForeign;

    _alphabetSize = alphabetSize;

    _calculateAndSetNumberOfStates();
}

Classifier::~Classifier(){
    for(int i = 0 ; i < _nativeLanguages->size(); i++)
        delete (*_nativeLanguages)[i];
    for(int i = 0 ; i < _foreignLanguages->size(); i++)
        delete (*_foreignLanguages)[i];
    delete _nativeLanguages;
    delete _foreignLanguages;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void Classifier::runClassification(){
    logger::log("Running Classifcation");

    logger::log("Selecting State Correspondence");
    _printStateCorrespondence();

    logger::log("Running PSO");
    PSO* pso = new PSO(_numberOfStates, _alphabetSize,
                        _nativeLanguages, _foreignLanguages);

    pso->compute();

};

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void Classifier::_printStateCorrespondence(){
    std::stringstream ss;
    ss << "[STATE CORRESPONDENCE]";
    for(int i = 0; i < _nativeLanguages->size(); i++){
        ss << "\nNative  Lan[" << i << "] ................................... ";
        ss << (*_nativeLanguages)[i]->statesToString();
    }
    for(int i = 0; i < _foreignLanguages->size(); i++){
        ss << "\nForeign Lan[" << i << "] ................................... ";
        ss << (*_foreignLanguages)[i]->statesToString();
    }
    logger::log(ss.str());
}


unsigned int Classifier::_calculateAndSetNumberOfStates(){
    int nativeSize = _nativeLanguages->size();
    int foreignSize = _foreignLanguages->size();

    _numberOfStates = nativeSize*_statesPerNative + _statesPerForeign;
}