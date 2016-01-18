//
// Created by jakub on 1/17/16.
//

#ifndef BACHELOR_THESIS_TRANSFORMATION_PRECISION_H
#define BACHELOR_THESIS_TRANSFORMATION_PRECISION_H

#include <vector>
#include <language/language.h>

namespace quality {

    /*
     * Computes the transformation precision of a set of languages.
     * Let I = Size of sum of intersections of all languages
     * Let U = Size of sum of unions of all languages
     * Precision = 1 - I/U
     *
     * Precision belongs to [0,1]
     */
    double computeTransformationPrecision(std::vector<Language*>* languages);
}

#endif //BACHELOR_THESIS_TRANSFORMATION_PRECISION_H
