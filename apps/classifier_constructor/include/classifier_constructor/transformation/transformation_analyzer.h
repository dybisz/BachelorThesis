//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_TRANSFORMATIONANALYZER_H
#define BACHELOR_THESIS_TRANSFORMATIONANALYZER_H

#include <patterns/pattern.h>
#include "classifier_constructor/transformation/transformation.h"

namespace transformation {

/**
 * Computes the Transformation Analysis on Classes
 */
class TransformationAnalyzer {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    std::vector<Pattern *> *patterns;

    int minAlphabetSize;
    int maxAlphabetSize;

    std::vector<TotalSimilarity> totalSimilarities;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    string getMutualResultsPlot(const TotalSimilarity &totalSimilarity);

    string getMutualResultsInfo(const TotalSimilarity &totalSimilarity);

    string getTotalSimilarityResultInfo(const TotalSimilarity &totalSimilarity);
public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    TransformationAnalyzer(std::vector<Pattern *> *patterns,
                           int minAlphabetSize,
                           int maxAlphabetSize);

    ~TransformationAnalyzer();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Starts the analysis between the classes
     */
    void runAnalysis();

    /*
     * Prints the results to the logs
     */
    void printResults();

};
}

#endif //BACHELOR_THESIS_TRANSFORMATIONANALYZER_H
