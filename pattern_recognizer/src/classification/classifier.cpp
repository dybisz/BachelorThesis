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
    _selectStateCorrespondence(_nativeLanguages, _foreignLanguages);
    _printStateCorrespondence();

    logger::log("Running PSO");
    PSO* pso = new PSO(_numberOfStates, _alphabetSize,
                        _nativeLanguages, _foreignLanguages);

    pso->compute();

    std::vector<Particle *> psoResults = pso->getBestParticles();
    Particle* firstBest = psoResults[0];

    // Quality results
    // ...
    // gooood quality mr Wladyslaw
};

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void Classifier::_selectStateCorrespondence(
        std::vector<Language*>* nativeLanguages,
        std::vector<Language*>* foreignLanguages){
    int nativeSize = nativeLanguages->size();
    int foreignSize = foreignLanguages->size();

    int statesPerNative = global_settings::STATES_PER_NATIVE;
    int statesPerForeign = global_settings::STATES_PER_FOREIGN;

    int currentStateKey = 0;

    for(int i = 0; i < nativeSize; i++){
        std::vector<State*> states;
        for(int j = 0; j < statesPerNative; j++){
            State* state = new State(currentStateKey);
            states.push_back(state);

            currentStateKey++;
        }
        (*nativeLanguages)[i]->setStates(states);
    }

    std::vector<State*> states;
    for(int i = 0; i < statesPerForeign; i++){
        State* state = new State(currentStateKey);
        states.push_back(state);

        currentStateKey++;
    }
    for(int i = 0; i < foreignSize; i++){
        (*foreignLanguages)[i]->setStates(states);
    }
}

void Classifier::_printStateCorrespondence(){
    std::stringstream ss;
    ss << "State correspondence" << std::endl;
    for(int i = 0; i < _nativeLanguages->size(); i++){
        ss << "Native Lan[" << i << "]" << std::endl;
        ss << (*_nativeLanguages)[i]->statesToString();
    }
    for(int i = 0; i < _foreignLanguages->size(); i++){
        ss << "Foreign Lan[" << i << "]" << std::endl;
        ss << (*_foreignLanguages)[i]->statesToString();
    }
    logger::log(ss.str());
}


unsigned int Classifier::_calculateAndSetNumberOfStates(){
    int nativeSize = _nativeLanguages->size();
    int foreignSize = _foreignLanguages->size();

    _numberOfStates = nativeSize*_statesPerNative + _statesPerForeign;
}