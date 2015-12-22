//
// Created by jakub on 12/22/15.
//

#include "classification_exp.h"
#include <loaders/xls_loader.h>
#include <settings/global_settings.h>
#include <logger/log.h>
#include <patterns_to_languages.h>

namespace experiments
{
    void runClassificationExperiment(){
        logger::log("Starting Classification Experiment");

        logger::log("Loading Patterns");

        // Note: if xlsLoader goes out of scope, patterns are deleted.
        XlsLoader nativeXLSLoader(global_settings::NATIVE_XLS_PATH);
        XlsLoader foreignXLSLoader(global_settings::FOREIGN_XLS_PATH);

        std::vector<Pattern*>* nativePatterns = nativeXLSLoader.getPatterns();
        std::vector<Pattern*>* foreignPatterns = foreignXLSLoader.getPatterns();

        classification::printLoadedPatternsInfo(nativePatterns, "Native");
        classification::printLoadedPatternsInfo(foreignPatterns, "Foreign");

        /* Transformation */
        logger::log("Language Transformation");

        std::vector<Language*>* nativeLanguages =
                patterns_to_languages::convert(
                        nativePatterns,
                        global_settings::STATES_PER_NATIVE,
                        global_settings::ALPHABET_SIZE);

        std::vector<Language*>* foreignLanguages =
                patterns_to_languages::convert(
                        nativePatterns,
                        global_settings::STATES_PER_FOREIGN,
                        global_settings::ALPHABET_SIZE);

        classification::printTransformedLanguagesInfo(nativeLanguages,
                                                      "Native");
        classification::printTransformedLanguagesInfo(foreignLanguages,
                                                      "Foreign");


        for(int i = 0 ; i < nativeLanguages->size(); i++)
            delete (*nativeLanguages)[i];
        for(int i = 0 ; i < foreignLanguages->size(); i++)
            delete (*foreignLanguages)[i];
        delete nativeLanguages;
        delete foreignLanguages;
    }

    namespace classification
    {
        void printLoadedPatternsInfo(std::vector<Pattern*>* patterns,
                                     std::string headerInfo){
            std::stringstream ss;
            ss << "Patterns. " << headerInfo << std::endl;
            ss << "Different Patterns count. "
                << patterns->size() << std::endl;

            int sum = 0;
            for(int i = 0; i < patterns->size(); i++){
                sum += (*patterns)[i]->size();
                ss << "Pattern["
                    << i
                    << "] count: "
                    << (*patterns)[i]->size() << std::endl;
            }
            ss << "All Patterns count: " << sum;

            logger::log(ss.str());
        }

        void printTransformedLanguagesInfo(std::vector<Language*>* languages,
                                            std::string headerInfo){
            std::stringstream ss;
            ss << "Languages. " << headerInfo << std::endl;
            ss << "Languages count " << languages->size() << std::endl;

            int sum = 0;
            for(int i = 0; i < languages->size(); i++){
                sum += (*languages)[i]->size();
                ss << "Language["
                << i
                << "] word count: "
                << (*languages)[i]->size() << std::endl;
            }
            ss << "All Words count: " << sum;

            logger::log(ss.str());
        }
    }
}