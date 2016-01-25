//
// Created by jakub on 1/19/16.
//

#ifndef BACHELOR_THESIS_TRANSFORMATION_H
#define BACHELOR_THESIS_TRANSFORMATION_H

#include <vector>
#include "class.h"
#include <sstream>
#include <language/language.h>

namespace transformation{

    /*
     * Stores results of Similarity analysis between two languages.
     */
    struct Similarity {
        int languageID1;
        int languageID2;
        int alphabetSize;
        double similarity;

        Similarity() {};

        Similarity(int languageID1, int languageID2,
                    int alphabetSize, double similarity) {
            this->languageID1 = languageID1;
            this->languageID2 = languageID2;
            this->alphabetSize = alphabetSize;
            this->similarity = similarity;
        };

    };

    /*
     * Stores result between analysis of Similarities
     */
    struct TotalSimilarity{
        std::vector<Similarity> results;
        int alphabetSize;
        double similarity;

        TotalSimilarity() {};

        TotalSimilarity(std::vector<Similarity> results,
                        int alphabetSize, double similarity) {
            this->results = results;
            this->alphabetSize = alphabetSize;
            this->similarity = similarity;
        };
    };


    /*
     * Computes similarity analysis between transformed languages
     * from given classes and alphabet size.
     */
    TotalSimilarity computeSimilarityAnalysis(std::vector<Class *> *patterns,
                                              int alphabetSize);

    /*
     * Get Distinct similarities between languages.
     * Distinct mean that equal languages are not considered.
     *
     * Returning Simlarity vector contains
     * similarity between all distinct pairs of languages.
     *
     * Similarity is computes by: language::averageSimilarity()
     */
    std::vector<Similarity> getDistinctSimilarites(
            std::vector<Language *>* languages,
            int alphabetSize);

    /*
     * Get similarities between languages.
     * Returning Simlarity vector contains
     * similarity between all distinct pairs of languages.
     *
     * Similarity is computes by: language::similarity()
     */
    std::vector<Similarity> getSimilarites(std::vector<Language *> *languages,
                                           int alphabetSize);

    /*
     * Gets the total similarity from all Similarites in the vector.
     * The Total similarity is the average from all Similarties.
     */
    TotalSimilarity getTotalSimilarity(std::vector<Similarity>& results,
                                       int alphabetSize);

}


#endif //BACHELOR_THESIS_TRANSFORMATION_H
