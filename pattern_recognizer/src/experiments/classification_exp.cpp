//
// Created by jakub on 12/22/15.
//

#include "classification_exp.h"
#include <loaders/xls_loader.h>
#include <settings/global_settings.h>
#include <logger/log.h>
#include <patterns_to_languages.h>
#include <classifier.h>

namespace experiments {
    void runClassificationExperiment() {
        logger::log("Starting Classification Experiment");

        logger::log("Loading Patterns");

        // Note: if xlsLoader goes out of scope, patterns are deleted.
        XlsLoader nativeXLSLoader(global_settings::NATIVE_XLS_PATH);
        XlsLoader foreignXLSLoader(global_settings::FOREIGN_XLS_PATH);

        std::vector<Pattern *> *nativePatterns = nativeXLSLoader.getPatterns();
        std::vector<Pattern *> *foreignPatterns = foreignXLSLoader.getPatterns();

        classification::printLoadedPatternsInfo(nativePatterns, "NATIVE");
        classification::printLoadedPatternsInfo(foreignPatterns, "FOREIGN");

        /* Transformation */
        logger::log("Language Transformation");

        std::vector<Language *> *nativeLanguages =
                patterns_to_languages::convert(nativePatterns,
                                               global_settings::ALPHABET_SIZE);

        std::vector<Language *> *foreignLanguages =
                patterns_to_languages::convert(foreignPatterns,
                                               global_settings::ALPHABET_SIZE);

//        classification::printTransformedLanguagesInfo(nativeLanguages,
//                                                      "NATIVE");
//        classification::printTransformedLanguagesInfo(foreignLanguages,
//                                                      "FOREIGN");

        Classifier *classifier = new Classifier(
                nativeLanguages,
                foreignLanguages,
                global_settings::STATES_PER_NATIVE,
                global_settings::STATES_PER_FOREIGN,
                global_settings::ALPHABET_SIZE,
                global_settings::TESTING_SET_RATIO);

        classifier->runClassification();
        delete classifier;

        // TODO memeory of alphabet from
        // TODO patterns_to_languages::convert is not fred
    }

    namespace classification {
        void printLoadedPatternsInfo(std::vector<Pattern *> *patterns,
                                     std::string headerInfo) {
            std::stringstream ss;
            ss << "[PATTERNS_" << headerInfo << "]\n";

            int sum = 0;
            for (int i = 0; i < patterns->size(); i++) {
                sum += (*patterns)[i]->size();
                ss << "Pattern["
                << i
                << "] ....................................... "
                << (*patterns)[i]->size() << std::endl;
            }
//            string temp = "\u222A";
            ss << "-------------------------------------------------+ " << sum;

            logger::log(ss.str());
        }
    }
}
