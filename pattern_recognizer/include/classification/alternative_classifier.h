//
// Created by dybisz on 30.12.15.
//

#ifndef BACHELOR_THESIS_ALTERNATIVE_CLASIFIER_H
#define BACHELOR_THESIS_ALTERNATIVE_CLASIFIER_H

#include <settings/global_settings.h>
#include <language.h>

class AlternativeClassifier {
    // Constructor compatible with classic classifier
    AlternativeClassifier(std::vector<Language*>* nativeLanguages,
                          std::vector<Language*>* foreignLanguages,
                          unsigned int statesPerNative,
                          unsigned int statesPerForeign,
                          unsigned int alphabetSize,
                          double testingSetRatio);

};

#endif //BACHELOR_THESIS_ALTERNATIVE_CLASIFIER_H
