//
// Created by jakub on 12/22/15.
//

#include "experiments/classification_exp.h"
#include <xls_loader.h>
#include <settings/global_settings.h>
#include <logger/log.h>
#include "classes_to_languages.h"
#include <classification/alternative_classifier.h>

using namespace pso;

namespace experiments {
    void runHillClimberBasedClassification() {
        logger::log("Starting Hill Climber Experiment");

        logger::log("Loading Patterns");

        // Note: if xlsLoader goes out of scope, patterns are deleted.
        XlsLoader nativeXLSLoader(settings::NATIVE_XLS_PATH,
                                  settings::NUMBER_OF_CLASSES,
                                  settings::PATTERNS_PER_CLASS);
        XlsLoader foreignXLSLoader(settings::FOREIGN_XLS_PATH,
                                   settings::NUMBER_OF_CLASSES,
                                   settings::PATTERNS_PER_CLASS);

        std::vector<Class *> *nativePatterns = nativeXLSLoader.getClasses();
        std::vector<Class *> *foreignPatterns = foreignXLSLoader.getClasses();

        classification::printLoadedPatternsInfo(nativePatterns, "NATIVE");
        classification::printLoadedPatternsInfo(foreignPatterns, "FOREIGN");

        /* Transformation */
        logger::log("Language Transformation");

        std::vector<Language *> *nativeLanguages =
                patterns_to_languages::convert(nativePatterns,
                                               settings::ALPHABET_SIZE);

        std::vector<Language *> *foreignLanguages =
                patterns_to_languages::convert(foreignPatterns,
                                               settings::ALPHABET_SIZE);

        AlternativeClassifier *classifier = new AlternativeClassifier(
                nativeLanguages,
                foreignLanguages,
                settings::HILL_CLIMBER_STATES,
                settings::ALPHABET_SIZE,
                settings::TESTING_SET_RATIO);

        classifier->compute();
        delete classifier;

    }

    namespace classification {
        void printLoadedPatternsInfo(std::vector<Class *> *patterns,
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
