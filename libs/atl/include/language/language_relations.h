//
// Created by jakub on 1/17/16.
//

#ifndef BACHELOR_THESIS_INTERSECTION_H
#define BACHELOR_THESIS_INTERSECTION_H

#include <language/language.h>

/**
 * Language Relations contains function defining any relations
 * between languages
 */

namespace language{

    /*
     * Gets intersection of two languages.
     *
     * Allocates memory.
     */
    Language* intersection(const Language& language1,
                           const Language& language2);

    /*
     * Constructs language which is a sum of intersections of all languages
     *
     */
    Language* intersectionSum(const std::vector<Language*>* languages);

    /*
     * Checks if two languages have equal alphabet.
     */
    bool equalAlphabets(const Language& language1, const Language& language2);

    /*
     * Checks if the set of languages have equal alphabet.
     */
    bool equalAlphabets(const std::vector<Language *> *languages);
}


#endif //BACHELOR_THESIS_INTERSECTION_H
