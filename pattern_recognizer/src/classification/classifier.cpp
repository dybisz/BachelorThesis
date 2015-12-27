//
// Created by jakub on 12/22/15.
//

#include <language.h>
#include <settings/global_settings.h>
#include <logger/log.h>
#include <pso.h>
#include <drawer.h>
#include <sets_ disassociation.h>
#include <language_algorithms.h>
#include <quality.h>
#include "classifier.h"


//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Classifier::Classifier(std::vector<Language *> *nativeLanguages,
                       std::vector<Language *> *foreignLanguages,
                       unsigned int statesPerNative,
                       unsigned int statesPerForeign,
                       unsigned int alphabetSize) {
    this->_nativeLanguages = nativeLanguages;
    this->_foreignLanguages = foreignLanguages;

    /* ----- TESTING SET ----- */
    double subsetRatio = 0.3; // TODO make flag
    this->_nativeTestingSet = set_disassociation::detachWords(subsetRatio,
                                                              _nativeLanguages);
    this->_foreignTestingSet = set_disassociation::detachWords(subsetRatio,
                                                               _foreignLanguages);
    /* ----------------------- */

    _statesPerNative = statesPerNative;
    _statesPerForeign = statesPerForeign;

    _alphabetSize = alphabetSize;

    _calculateAndSetNumberOfStates();
}

Classifier::Classifier(std::vector<Language*>* nativeLanguages,
                        std::vector<Language*>* foreignLanguages,
                        unsigned int statesPerNative,
                        unsigned int statesPerForeign,
                        unsigned int alphabetSize,
                        double testingSetRatio){
    this->_nativeLanguages = nativeLanguages;
    this->_foreignLanguages = foreignLanguages;

    // TODO integers -> states
    quality::_convertWords(_nativeLanguages);
    quality::_convertWords(_foreignLanguages);

    this->_nativeTestingSet =
            set_disassociation::detachWords(testingSetRatio,
                                            _nativeLanguages);
    this->_foreignTestingSet =
            set_disassociation::detachWords(testingSetRatio,
                                            _foreignLanguages);

    _statesPerNative = statesPerNative;
    _statesPerForeign = statesPerForeign;

    _alphabetSize = alphabetSize;

    _calculateAndSetNumberOfStates();
}

Classifier::~Classifier() {
    for (int i = 0; i < _nativeLanguages->size(); i++)
        delete (*_nativeLanguages)[i];
    for (int i = 0; i < _foreignLanguages->size(); i++)
        delete (*_foreignLanguages)[i];
    for (int i = 0; i < _nativeTestingSet->size(); i++)
        delete (*_nativeTestingSet)[i];
    if(_foreignTestingSet != NULL){
        for (int i = 0; i < _foreignTestingSet->size(); i++)
            delete (*_foreignTestingSet)[i];

        delete _foreignTestingSet;
    }
    delete _nativeLanguages;
    delete _foreignLanguages;
    delete _nativeTestingSet;

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

unsigned int Classifier::getStateCount() const{
    return this->_numberOfStates;
}

const std::vector<Language*>* Classifier::getNativeTrainingLanguages() const{
    return this->_nativeLanguages;
}

const std::vector<Language*>* Classifier::getNativeTestingLanguages() const {
    return this->_nativeTestingSet;
}

const std::vector<Language*>* Classifier::getForeignLanguages() const {
    return this->_foreignLanguages;
}

void Classifier::runClassification() {
    languages::selectStateCorrespondence(this->_nativeLanguages,
                                         this->_foreignLanguages,
                                         this->_statesPerNative,
                                         this->_statesPerForeign);

    _printSetInfo(_nativeLanguages, "NATIVE_TRAINING");
    _printSetInfo(_foreignLanguages, "FOREIGN_TRAINING");
    _printSetInfo(_nativeTestingSet, "NATIVE_TESTING");
    _printSetInfo(_foreignTestingSet, "FOREIGN_TESTING");
    _printStateCorrespondence();

    logger::log("Running PSO");
    PSO *pso = new PSO(_numberOfStates, _alphabetSize,
                       _nativeLanguages, _foreignLanguages);

    pso->compute();

    std::vector<Particle *> psoResults = pso->getBestParticles();
    Particle* firstBest = psoResults[0];
    const DFA* bestDFA = firstBest->getBestDFA();

    _calculateAndPrintQualityResults(bestDFA);
};

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void Classifier::_calculateAndPrintQualityResults(const DFA* bestDFA){
    std::string trainingInfo    = "TRAINING";
    std::string testingInfo     = "TESTING";

    logger::log(quality::distinctResultsToString(_nativeLanguages,
                                                 _foreignLanguages,
                                                 (DFA *) bestDFA,
                                                 trainingInfo));
    logger::log(quality::overallResultsToString(_nativeLanguages,
                                                _foreignLanguages,
                                                (DFA *) bestDFA,
                                                trainingInfo));

    logger::log(quality::distinctResultsToString(_nativeTestingSet,
                                                 _foreignTestingSet,
                                                 (DFA *) bestDFA,
                                                 testingInfo));
    logger::log(quality::overallResultsToString(_nativeTestingSet,
                                                _foreignTestingSet,
                                                (DFA *) bestDFA,
                                                testingInfo));
}

void Classifier::_printStateCorrespondence() {
    std::stringstream ss;
    ss << "[STATE CORRESPONDENCE]";
    for (int i = 0; i < _nativeLanguages->size(); i++) {
        ss << "\nNative  Lan[" << i << "] ................................... ";
        ss << (*_nativeLanguages)[i]->statesToString();
    }
    for (int i = 0; i < _foreignLanguages->size(); i++) {
        ss << "\nForeign Lan[" << i << "] ................................... ";
        ss << (*_foreignLanguages)[i]->statesToString();
    }
    logger::log(ss.str());
}

void Classifier::_printSetInfo(std::vector<Language *> *pLanguages,
                               std::string setName) {
    std::stringstream ss;
    ss << "[LANGUAGES_" << setName << "]\n";

    int sum = 0;
    for (int i = 0; i < pLanguages->size(); i++) {
        sum += (*pLanguages)[i]->size();
        ss << "Language["
        << i
        << "] ...................................... "
        << (*pLanguages)[i]->size() << std::endl;
    }
    ss << "-------------------------------------------------+ " << sum;
    logger::log(ss.str());
}

unsigned int Classifier::_calculateAndSetNumberOfStates() {
    int nativeSize = _nativeLanguages->size();
    int foreignSize = _foreignLanguages->size();

    _numberOfStates = nativeSize * _statesPerNative + _statesPerForeign;
}
