//
// Created by jakub on 1/20/16.
//

#include <logger/log.h>
#include "classifier_constructor/transformation/transformation_analyzer.h"

namespace transformation{

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

TransformationAnalyzer::TransformationAnalyzer(
                                std::vector<Pattern *>* patterns,
                                int minAlphabetSize,
                                int maxAlphabetSize) {
    this->patterns = patterns;
    this->minAlphabetSize = minAlphabetSize;
    this->maxAlphabetSize = maxAlphabetSize;
}

TransformationAnalyzer::~TransformationAnalyzer() {

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void TransformationAnalyzer::runAnalysis() {
    for(unsigned int r = minAlphabetSize; r <= maxAlphabetSize; r++){
        TotalSimilarity totalSimilarity
                = computeSimilarityAnalysis(patterns, r);
        totalSimilarities.push_back(totalSimilarity);
        logger::log("Alphabet size: ", r,
                    " Total Similarity: ", totalSimilarity.similarity);
    }
}

void TransformationAnalyzer::printResults(){
    std::stringstream info;
    info << "# Transfomation Precision Plot" << std::endl;
    info << "# x: Alphabet Size" << std::endl;
    info << "# y: Total Similarity" << std::endl;
    info << "addPlot[] coordinates{" << std::endl;
    for(unsigned int i = 0; i < totalSimilarities.size(); i++){
        info << "("
        << totalSimilarities[i].alphabetSize
        << ", "
        << totalSimilarities[i].similarity
        << ")" << std::endl;
    }
    info << "}" << std::endl;
    info << std::endl;
    logger::log(File("SimilarityPlot.txt", false), info.str());
}

}