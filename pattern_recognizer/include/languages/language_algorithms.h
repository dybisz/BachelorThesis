//
// Created by jakub on 12/27/15.
//

#ifndef BACHELOR_THESIS_LANGUAGE_ALGORITHMS_H
#define BACHELOR_THESIS_LANGUAGE_ALGORITHMS_H

#include <vector>
#include <settings/global_settings.h>
#include "language.h"

namespace languages
{
    /*
     * Selects state correspondence of native and foreign languages
     */
    void selectStateCorrespondence(std::vector<Language*>* nativeLanguages,
                                    std::vector<Language*>* foreignLanguages,
                                    unsigned int statesPerNative,
                                    unsigned int statesPerForeign);
}

#endif //BACHELOR_THESIS_LANGUAGE_ALGORITHMS_H
