//
// Created by jakub on 12/27/15.
//

#ifndef BACHELOR_THESIS_LANGUAGE_ALGORITHMS_H
#define BACHELOR_THESIS_LANGUAGE_ALGORITHMS_H

#include <vector>
#include "language/language.h"

namespace language
{
    /*
     * Selects state correspondence
     * of native and foreign languages.
     *
     * Each native language receives unique
     * set of states of size statesPerNative.
     *
     * All foreign languages are treated as one
     * and thus all receive the same set of states
     * of size statesPerForeign.
     */
    void selectStateCorrespondence(std::vector<Language*>* nativeLanguages,
                                    std::vector<Language*>* foreignLanguages,
                                    unsigned int statesPerNative,
                                    unsigned int statesPerForeign);


    /*
     * Returns number of cccurrences of input word in input vector of words
     */
    int numberOfOccurrences(const vector<Word*>& words,
                            const Word& word);
}

#endif //BACHELOR_THESIS_LANGUAGE_ALGORITHMS_H
