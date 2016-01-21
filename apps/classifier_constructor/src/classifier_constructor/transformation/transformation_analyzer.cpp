//
// Created by jakub on 1/20/16.
//

#include <logger/log.h>
#include <cmath>
#include <iomanip>
#include "classifier_constructor/transformation/transformation_analyzer.h"

using namespace std;

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

        string totalSimilarityInfo
                = getTotalSimilarityResultInfo(totalSimilarity);
        string mutualResultsPlot = getMutualResultsPlot(totalSimilarity);
        string mutualResultsInfo = getMutualResultsInfo(totalSimilarity);

        logger::log(totalSimilarityInfo);
        logger::log(File("MutualSimilarityPlot", false), mutualResultsPlot);
        logger::log(mutualResultsInfo);
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


//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

string TransformationAnalyzer::getTotalSimilarityResultInfo(
        const TotalSimilarity &totalSimilarity){
    string info = "Alphabet size: ";
    info += to_string(totalSimilarity.alphabetSize);
    info += " Total Similarity: ";
    info += to_string(totalSimilarity.similarity);

    return info;
}

string TransformationAnalyzer::getMutualResultsPlot(
        const TotalSimilarity &totalSimilarity){
    vector<Similarity> mutualSimilarities = totalSimilarity.results;
    string SYMBOL_SEPERATOR = "&";
    string ROW_SEPERATOR = "\\\\ \n \\hline \n";

    stringstream ss;
    int FLOAT_PRINT_PRECISION = 2;
    ss << setprecision(FLOAT_PRINT_PRECISION);

    int size = mutualSimilarities.size();
    int languageCount = std::sqrt(size);

    for(unsigned int i = 0; i < size; i++){
        Similarity similarity = mutualSimilarities[i];
        if(i != 0 && (i%languageCount==0)) {
            ss << ROW_SEPERATOR;
        }

        ss << SYMBOL_SEPERATOR << similarity.similarity;
    }
    ss << ROW_SEPERATOR;
    return ss.str();
}

string TransformationAnalyzer::getMutualResultsInfo(
        const TotalSimilarity &totalSimilarity){
    vector<Similarity> mutualSimilarities = totalSimilarity.results;
    string SYMBOL_SEPERATOR = "&";
    string ROW_SEPERATOR = "\\\\";

    stringstream ss;
    int FLOAT_PRINT_PRECISION = 2;
    ss << setprecision(FLOAT_PRINT_PRECISION);

    int size = mutualSimilarities.size();
    int languageCount = std::sqrt(size);

    for(unsigned int i = 0; i < size; i++){
        Similarity similarity = mutualSimilarities[i];

        ss << "L" << similarity.languageID1;
        ss << " : ";
        ss << "L" << similarity.languageID2;
        ss << " = " << similarity.similarity;

        if(i != 0 && (i%languageCount==0))
            ss << "\n";
        else{
            ss <<  "\t";
        }
    }
    return ss.str();
}

}
