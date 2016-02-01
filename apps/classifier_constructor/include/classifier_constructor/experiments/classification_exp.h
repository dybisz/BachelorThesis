//
// Created by jakub on 12/22/15.
//

#ifndef BACHELOR_THESIS_CLASSIFICATION_EXP_H
#define BACHELOR_THESIS_CLASSIFICATION_EXP_H

#include "class.h"
#include <language/language.h>
#include <vector>
#include <pso/particle_updater.h>
#include <transformation/transformation.h>

#include <classifier/pso/pso_factory.h>
#include <classifier/classifier.h>

using namespace transformation;

/*
 * Provides functionality for classification experiments.
 * All the settings used come from the application settings
 */
namespace classification_experiment
{
    /*
     * Starts classification experiments.
     * All of the settings are taken from application settings.
     */
    void runClassification();

    PSOFactory getPSOFactory(vector<Language*>* native,
                             vector<Language*>* foreign);

    Classifier* getClassifier(PSO* pso, TransformedLanguages& languages);

    void setUpStateCorrespondence(TransformedLanguages& languages);

    /*
     * Returns testing set seperated from input languages
     */
    TransformedLanguages seperateTestingLanguages(
            TransformedLanguages languages, double testingSetRatio);

    void calculateAndPrintQualityResults(const DFA* classifierDFA,
                                         vector<Language *> *nativeLanguages,
                                         vector<Language *> *foreignLanguages,
                                         std::string info);

    void printStateCorrespondence(std::vector<Language *>* langauges,
                                  std::string info);


}
#endif //BACHELOR_THESIS_CLASSIFICATION_EXP_H