//
// Created by jakub on 1/24/16.
//

#include <transformation/transformation.h>
#include <transformation/transformation_analyzer.h>
#include <classifier_quality.h>
#include <language/language_algorithms.h>
#include <classifier_constructor/cfac_construction/fac_builder.h>
#include "classifier_constructor/cfac_construction/cfac_builder.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

CFACBuilder::CFACBuilder(vector<Language*>* nativeLanguages,
                         vector<Language*>* foreignLanguages,
                         int statesPerNative,
                         int statesPerForeign,
                         PSOFactory* psoFactory) :
        FOREIGN_LABEL(FOREIGN_LABEL_VALUE){
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;

    this->statesPerNative = statesPerNative;
    this->statesPerForeign = statesPerForeign;

    this->psoFactory = psoFactory;

    classifier = NULL;
}

CFACBuilder::~CFACBuilder() {
    if(classifier != NULL)
        delete classifier;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void CFACBuilder::build() {

}

void CFACBuilder::build(int alphabetSize) {
    vector<FAC> facClassifiers = buildFACClassifiers(nativeLanguages,
                                                     foreignLanguages,
                                                     alphabetSize);
    this->classifier = new CFAC(facClassifiers, alphabetSize);
}

const CFAC &CFACBuilder::getClassifier() const{
    if(classifier == NULL){
        throw invalid_argument("Can not acces Classifier before build");
    }
    return *classifier;
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

std::vector<FAC> CFACBuilder::buildFACClassifiers(
        std::vector<Language *> *nativeLanguages,
        std::vector<Language *> *foreignLanguages,
        int alphabetSize) {
    vector<FAC> facClassifiers;
    for(unsigned int i = 0; i < nativeLanguages->size(); i++){
        Label nativeLabel(i);
        FAC fac = buildBinaryFAC((*nativeLanguages)[i], nativeLabel,
                                 (*foreignLanguages)[i], FOREIGN_LABEL,
                                 alphabetSize);
        facClassifiers.push_back(fac);
    }

    return facClassifiers;
}


FAC CFACBuilder::buildBinaryFAC(Language* nativeLanguage,
                                Label nativeLabel,
                                Language* foreignLanguage,
                                Label foreignLabel,
                                int alphabetSize) {
    vector<Language*> tmpNativeLanguages{nativeLanguage};
    vector<Language*> tmpForeignLanguages{foreignLanguage};
    language::selectStateCorrespondence(&tmpNativeLanguages,
                                        &tmpForeignLanguages,
                                        statesPerNative, statesPerForeign);

    Correspondence correspondence
            = createCorrespondece(nativeLanguage, nativeLabel,
                                  foreignLanguage, foreignLabel);

    PSO* pso = psoFactory->createPSO(&tmpNativeLanguages, &tmpForeignLanguages,
                                     statesPerNative, statesPerForeign,
                                     alphabetSize);

    FACBuilder facBuilder(correspondence, pso);
    facBuilder.build();
    const FAC& fac = facBuilder.getClassifier();

    delete pso;

    return fac;
}

Correspondence CFACBuilder::createCorrespondece(
        Language *nativeLanguage,
        Label nativeLabel,
        Language *foreignLanguage,
        Label foreignLabel) {
    Correspondence correspondence;

    vector<State*>* nativeStates = nativeLanguage->getStates();
    for(unsigned int i = 0; i < nativeStates->size(); i++){
        State* state = (*nativeStates)[i];
        correspondence.addCorrespondence(nativeLabel, *state);
    }

    vector<State*>* foreignStates = foreignLanguage->getStates();
    for(unsigned int i = 0; i < foreignStates->size(); i++){
        State* state = (*foreignStates)[i];
        correspondence.addCorrespondence(foreignLabel, *state);
    }

    return correspondence;
}


int CFACBuilder::computeAlphabetSize(std::vector<Class *>* nativeClasses) {
    //transformation::TransformationAnalyzer transformationAnalyzer;
    return 0;
}
