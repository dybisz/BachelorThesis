//
// Created by jakub on 12/22/15.
//

#ifndef BACHELOR_THESIS_CLASSIFICATION_EXP_H
#define BACHELOR_THESIS_CLASSIFICATION_EXP_H

#include "class.h"
#include "classifier.h"
#include <language/language.h>
#include <vector>
#include <pso/particle_updater.h>
#include <classifier_constructor/pso_classifier/pso_factory.h>
#include <transformation/transformation.h>

namespace classification_experiment
{
    void runClassification();

    PSOFactory getPSOFactory(vector<Language*>* native,
                             vector<Language*>* foreign);

    Classifier* getClassifier(PSO* pso,
                              transformation::TransformedLanguages& languages);

    void printLoadedClassesInfo(std::vector<Class *> *patterns,
                                std::string headerInfo);

}
#endif //BACHELOR_THESIS_CLASSIFICATION_EXP_H