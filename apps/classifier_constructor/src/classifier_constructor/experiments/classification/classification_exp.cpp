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

#include <classifier_constructor/experiments/binary_classification.h>
#include <classifier_constructor/experiments/common.h>

using namespace pso;
using namespace transformation;
using namespace experiments;

namespace classification_experiment {
    void runClassification(){
        XlsLoader nativeXLSLoader = getNativeXLSLoader();
        XlsLoader foreignXLSLoader = getForeignXLSLoader();
        TransformedLanguages languages = getLanguages(nativeXLSLoader,
                                                      foreignXLSLoader);

        PSOFactory psoFactory = getPSOFactory(languages.native,
                                              languages.foreign);
        PSO* pso = psoFactory.createPSO();

        Classifier *classifier = getClassifier(pso, languages);

        classifier->runClassification();
        delete classifier;
    }

    PSOFactory getPSOFactory(vector<Language*>* native,
                             vector<Language*>* foreign) {
        FitnessType fitnessType
                = static_cast<FitnessType>(settings::FITNESS_TYPE);
        logger::log("Fitness Type: ", fitnessType);
        PSOFactory psoFactory(
                native, foreign,
                settings::STATES_PER_NATIVE, settings::STATES_PER_FOREIGN,
                settings::ALPHABET_SIZE,
                settings::SWARM_SIZE, settings::MAX_ITER,
                settings::TRUE_THREAD_COUNT,
                settings::MAX_VELOCITY,
                settings::ENCODING_DELTA, settings::UPPER_BOUND_ERR,
                settings::LEARNING_FACTOR, settings::PARTICLE_VEL_WEIGHT,
                fitnessType
        );
        return psoFactory;
    }

    Classifier* getClassifier(PSO* pso, TransformedLanguages& languages){
        Classifier *classifier
                = new Classifier(pso, languages.native, languages .foreign,
                                 settings::STATES_PER_NATIVE,
                                 settings::STATES_PER_FOREIGN,
                                 settings::ALPHABET_SIZE,
                                 settings::TESTING_SET_RATIO);
        return classifier;
    }

    void printLoadedClassesInfo(std::vector<Class *> *patterns,
                                std::string headerInfo) {
        std::stringstream ss;
        ss << "[Classes_" << headerInfo << "]\n";

        int sum = 0;
        for (int i = 0; i < patterns->size(); i++) {
            sum += (*patterns)[i]->size();
            ss << "Class["
            << i
            << "] ....................................... "
            << (*patterns)[i]->size() << std::endl;
        }

        ss << "-------------------------------------------------+ " << sum;

        logger::log(ss.str());
    }
}
