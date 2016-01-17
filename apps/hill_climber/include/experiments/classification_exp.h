//
// Created by jakub on 12/22/15.
//

#ifndef BACHELOR_THESIS_CLASSIFICATION_EXP_H
#define BACHELOR_THESIS_CLASSIFICATION_EXP_H

#include "patterns/pattern.h"
#include <vector>
#include <language/language.h>

namespace experiments
{
    void runHillClimberBasedClassification();

    namespace classification
    {
        void printLoadedPatternsInfo(std::vector<Pattern*>* patterns,
                                     std::string headerInfo);
    }
}
#endif //BACHELOR_THESIS_CLASSIFICATION_EXP_H