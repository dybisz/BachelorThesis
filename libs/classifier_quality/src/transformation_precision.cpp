//
// Created by jakub on 1/17/16.
//

#include <patterns_to_languages.h>
#include "transformation_precision.h"

namespace quality {

    double computeTransformationPrecision(Pattern& pattern,
                                          int alphabetSize){
        Language* language = patterns_to_languages::convert(pattern,
                                                            alphabetSize);
        language->removeDuplicates();

        double objectsCount = pattern.size();
        double transformedSize = language->size();

        double ratio = ((double)transformedSize/(double)objectsCount);

        delete language;

        return ratio;
    }
}