//
// Created by jakub on 12/22/15.
//

#ifndef BACHELOR_THESIS_CLASSIFICATION_EXP_H
#define BACHELOR_THESIS_CLASSIFICATION_EXP_H

#include <patterns/pattern.h>
#include <language/language.h>
#include <vector>
#include <pso/particle_updater.h>
#include <classifier_constructor/pso_classifier/dfa_fitness_updater.h>

namespace experiments
{
    void runClassification();

    void printLoadedPatternsInfo(std::vector<Pattern*>* patterns,
                                 std::string headerInfo);

}
#endif //BACHELOR_THESIS_CLASSIFICATION_EXP_H