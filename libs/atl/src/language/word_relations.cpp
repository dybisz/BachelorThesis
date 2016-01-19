//
// Created by jakub on 1/19/16.
//

#include "language/word_relations.h"

namespace word {

    int hammingDistance(const Word &word1, const Word &word2) {
        if (word1.size() != word2.size()){
            throw std::invalid_argument("Words sizes must match");
        }

        int deltaCounter = 0;
        for(int i = 0; i < word1.size(); i++){
            Symbol* symbol1 = word1.getSymbol(i);
            Symbol* symbol2 = word2.getSymbol(i);
            if (!(*symbol1 == *symbol2)){
                deltaCounter++;
            }
        }
        return deltaCounter;
    }

    double similarity(const Word &word1, const Word &word2) {
        int hammingDistance = word::hammingDistance(word1, word2);
        int size = word1.size();

        double similarity = (double)hammingDistance/size;
        int NORMALIZER = 1;
        return NORMALIZER - similarity;
    }
}