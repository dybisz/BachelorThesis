//
// Created by jakub on 1/19/16.
//

#include <transformation_precision.h>
#include "classes_to_languages.h"
#include <language/language_relations.h>
#include <logger/log.h>
#include "classifier_constructor/transformation/transformation.h"

namespace transformation{

    TotalSimilarity computeSimilarityAnalysis(std::vector<Class *> *patterns,
                                              int alphabetSize){
        std::vector<Language*>* languages =
                patterns_to_languages::convert(patterns, alphabetSize);

        std::vector<Similarity> similarites =
                getSimilarites(languages, alphabetSize);

        TotalSimilarity totalSimilarity = getTotalSimilarity(similarites,
                                                             alphabetSize);

        for(unsigned int i = 0 ; i < languages->size(); i++){
            delete (*languages)[i];
        }
        delete languages;

        return totalSimilarity;
    }
/*
    std::vector<Similarity> getSimilarites(std::vector<Language *> *languages,
                                           int alphabetSize){
        unsigned int languageCount = languages->size();
        std::vector<Similarity> results;
        for(unsigned int i = 0; i < languageCount - 1; i++){
            Language* language1 = (*languages)[i];
            for(unsigned int j = i+1; j < languageCount; j++){
                Language* language2 = (*languages)[j];
                double similarity = language::averageSimilarity(*language1,
                                                                *language2);
                Similarity result(i, j, alphabetSize, similarity);
                results.push_back(result);
            }
        }
        return results;
    }
*/
    std::vector<Similarity> getSimilarites(std::vector<Language *> *languages,
                                           int alphabetSize){
        unsigned int languageCount = languages->size();
        std::vector<Similarity> results;
        for(unsigned int i = 0; i < languageCount; i++){
            Language* language1 = (*languages)[i];
            for(unsigned int j = 0; j < languageCount; j++){
                Language* language2 = (*languages)[j];
                double similarity = language::similarity(*language1,
                                                         *language2);
                Similarity result(i, j, alphabetSize, similarity);
                results.push_back(result);
            }
        }
        return results;
    }

    TotalSimilarity getTotalSimilarity(std::vector<Similarity>& results,
                                       int alphabetSize){
        double averageSimilarity = 0;
        unsigned int resultsCount = results.size();
        for(unsigned int i = 0; i < resultsCount; i++){
            averageSimilarity += results[i].similarity;
        }
        averageSimilarity /= resultsCount;

        TotalSimilarity totalSimilarity(results,
                                        alphabetSize,
                                        averageSimilarity);

        return totalSimilarity;
    }

}