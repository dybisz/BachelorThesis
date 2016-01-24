//
// Created by jakub on 12/22/15.
//

#include <classifier_constructor/experiments/classification/classification_exp.h>
#include <classifier_constructor/experiments/classification/classifier.h>

#include <logger/log.h>
#include "transformation/transformation.h"

#include <xls_loader.h>

#include <classifier_constructor/settings/thread_settings.h>
#include <classifier_constructor/settings/pso_settings.h>
#include <classifier_constructor/settings/log_settings.h>
#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_constructor/settings/app_settings.h>

#include <classifier_constructor/experiments/classification/pso_factory.h>

using namespace pso;

namespace experiments {

    void runClassification(){
        logger::log("Starting PSO Experiment");

        logger::log("Loading Patterns");

        // Note: if xlsLoader goes out of scope, patterns are deleted.
        XlsLoader nativeXLSLoader(settings::NATIVE_XLS_PATH,
                                  settings::NUMBER_OF_CLASSES,
                                  settings::PATTERNS_PER_CLASS);

        XlsLoader foreignXLSLoader(settings::FOREIGN_XLS_PATH,
                                   settings::NUMBER_OF_CLASSES,
                                   settings::PATTERNS_PER_CLASS);

        std::vector<Class *> *nativePatterns
                = nativeXLSLoader.getClasses();
        std::vector<Class *> *foreignPatterns
                = foreignXLSLoader.getClasses();

        printLoadedClassesInfo(nativePatterns, "NATIVE PATTERNS");
        printLoadedClassesInfo(foreignPatterns, "FOREIGN PATTERNS");

        logger::log("Transforming Patterns to Languages");

        std::vector<Language *> *nativeLanguages
                = transformation::convert(nativePatterns,
                                          settings::ALPHABET_SIZE);
        std::vector<Language *> *foreignLanguages
                = transformation::convert(foreignPatterns,
                                          settings::ALPHABET_SIZE);

        PSOFactory psoFactory(
                nativeLanguages, foreignLanguages,
                settings::STATES_PER_NATIVE, settings::STATES_PER_FOREIGN,
                settings::ALPHABET_SIZE,
                settings::SWARM_SIZE, settings::MAX_ITER,
                settings::TRUE_THREAD_COUNT,
                settings::MAX_VELOCITY,
                settings::ENCODING_DELTA, settings::UPPER_BOUND_ERR,
                settings::LEARNING_FACTOR, settings::PARTICLE_VEL_WEIGHT
        );
        PSO* pso = psoFactory.createPSO();

        Classifier *classifier
                = new Classifier(pso,
                                 nativeLanguages,
                                 foreignLanguages,
                                 settings::STATES_PER_NATIVE,
                                 settings::STATES_PER_FOREIGN,
                                 settings::ALPHABET_SIZE,
                                 settings::TESTING_SET_RATIO);

        logger::log("Starting Classification");

        classifier->runClassification();
    }

    void printLoadedClassesInfo(std::vector<Class *> *patterns,
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

        ss << "-------------------------------------------------+ " << sum;

        logger::log(ss.str());
    }
}
