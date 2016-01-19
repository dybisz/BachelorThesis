//
// Created by jakub on 1/17/16.
//

#ifndef BACHELOR_THESIS_TRANSFORMATION_PRECISION_H
#define BACHELOR_THESIS_TRANSFORMATION_PRECISION_H

#include <vector>
#include <language/language.h>
#include <patterns/pattern.h>

namespace quality {

    /*
     * Transformation Precision is a ratio of
     * transformed language size (without duplicating words)
     * to the size of the pattern recognition object.
     */
    double computeTransformationPrecision(Pattern& pattern,
                                          int alphabetSize);

}

#endif //BACHELOR_THESIS_TRANSFORMATION_PRECISION_H
