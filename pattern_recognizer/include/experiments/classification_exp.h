//
// Created by jakub on 12/22/15.
//

#ifndef BACHELOR_THESIS_CLASSIFICATION_EXP_H
#define BACHELOR_THESIS_CLASSIFICATION_EXP_H

#include "pattern.h"
#include <vector>

namespace experiments
{
    /*
     * Starts the entire classification
     * experiment logic
     */
    void runClassificationExperiment();

    namespace classification
    {
        void printLoadedPatternsInfo(std::vector<Pattern*>* patterns,
                                     std::string headerInfo);
    }
}
#endif //BACHELOR_THESIS_CLASSIFICATION_EXP_H