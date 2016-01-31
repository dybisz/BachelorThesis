//
// Created by jakub on 12/22/15.
//

#include "experiments/classification_exp.h"
#include <xls_loader.h>
#include <settings/global_settings.h>
#include <logger/log.h>
#include "transformation/transformation.h"
#include <classification/alternative_classifier.h>
//#include </home/dybisz/Repositories/BachelorThesis/apps/classifier_constructor/include/classifier_constructor/experiments/common.h>

using namespace pso;
using namespace transformation;

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
//        logger::log("Language Transformation");
//        std::vector<Language *> *nativeLanguages =
//                transformation::transform(nativePatterns,
//                                          settings::ALPHABET_SIZE);
//
//        std::vector<Language *> *foreignLanguages =
//                transformation::transform(foreignPatterns,
//                                          settings::ALPHABET_SIZE);

//        TransformedLanguages languages = getLanguages(nativeXLSLoader,
//                                                      foreignXLSLoader);

        std::vector<Class *> *nativeClasses = nativeXLSLoader.getClasses();
        std::vector<Class *> *foreignClasses = foreignXLSLoader.getClasses();

        TransformationClasses classes(nativeClasses, foreignClasses);
        TransformedLanguages languages = transform(classes,
                                                   settings::ALPHABET_SIZE);

        AlternativeClassifier *classifier = new AlternativeClassifier(
                languages.native,
                languages.foreign,
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
