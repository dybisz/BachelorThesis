//
// Created by jakub on 12/22/15.
//

#include "classifier_constructor/experiments/classification_exp.h"

#include <logger/log.h>

#include <xls_loader.h>

#include <classifier_constructor/settings/thread_settings.h>
#include <classifier_constructor/settings/pso_settings.h>
#include <classifier_constructor/settings/log_settings.h>
#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_constructor/settings/app_settings.h>

#include <classifier_constructor/experiments/common.h>

#include <transformation/sets_disassociation.h>
#include <classifier_quality.h>
#include <language/language_algorithms.h>

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

        setUpStateCorrespondence(languages);
        TransformedLanguages testingLanguages
                = seperateTestingLanguages(languages,
                                           settings::TESTING_SET_RATIO);

        Classifier *classifier = getClassifier(pso, languages);
        classifier->runClassification();

        const DFA& classifierDFA = classifier->getClassiferDFA();

        calculateAndPrintQualityResults(&classifierDFA,
                                        languages.native,
                                        languages.foreign, "TRAINING");
        calculateAndPrintQualityResults(&classifierDFA,
                                        testingLanguages.native,
                                        testingLanguages.foreign, "TESTNG");
        delete classifier;
        deleteLanguages(testingLanguages.native);
        deleteLanguages(testingLanguages.foreign);
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
                = new Classifier(pso, languages.native, languages .foreign);
        return classifier;
    }

    void setUpStateCorrespondence(TransformedLanguages& languages){
        language::selectStateCorrespondence(languages.native, languages.foreign,
                                            settings::STATES_PER_NATIVE,
                                            settings::STATES_PER_FOREIGN);
        printStateCorrespondence(languages.native);
        printStateCorrespondence(languages.foreign);
    }

    TransformedLanguages seperateTestingLanguages(
            TransformedLanguages languages, double testingSetRatio){

        vector<Language *>* nativeTestingSet
                = set_disassociation::detachWords(testingSetRatio,
                                                  (languages.native));
        vector<Language *>* foreignTestingSet
                = set_disassociation::detachWords(testingSetRatio,
                                                  languages.foreign);

        TransformedLanguages testingLanguages{nativeTestingSet,
                                              foreignTestingSet};

        return testingLanguages;
    }

    void printStateCorrespondence(std::vector<Language *>* langauges) {
        std::stringstream ss;
        ss << "[STATE CORRESPONDENCE]";
        for (int i = 0; i < langauges->size(); i++) {
            ss << "\nNative  Lan[" << i << "] ............................... ";
            ss << (*langauges)[i]->statesToString();
        }
        logger::log(ss.str());
    }

    void calculateAndPrintQualityResults(const DFA* classifierDFA,
                                         vector<Language *> *nativeLanguages,
                                         vector<Language *> *foreignLanguages,
                                         std::string info){
        std::string resultFileName = "results.txt";

        logger::log(File(resultFileName, false),
                    quality::distinctResultsToString(nativeLanguages,
                                                     foreignLanguages,
                                                     (DFA *) classifierDFA,
                                                     info));
        logger::log(File(resultFileName, false),
                    quality::overallResultsToString(nativeLanguages,
                                                    foreignLanguages,
                                                    (DFA *) classifierDFA,
                                                    info));
    }

}
