//
// Created by jakub on 1/19/16.
//

#ifndef BACHELOR_THESIS_WORD_RELATIONS_H
#define BACHELOR_THESIS_WORD_RELATIONS_H

#include "language/word.h"

namespace word{

    /*
     * Computes the hamming distance between two words
     */
    int hammingDistance(const Word& word1,
                        const Word& word2);

    /*
     * Similarity of two words is equal to:
     * 1 - the ratio between hamming distance
     * and the words size.
     *
     * Thus equal words are similar
     */
    double similarity(const Word& word1,
                      const Word& word2);
}

#endif //BACHELOR_THESIS_WORD_RELATIONS_H
