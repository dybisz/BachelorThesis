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

    void runGroupedClassification() {
        XlsLoader nativeXLSLoader = getNativeXLSLoader();
        XlsLoader foreignXLSLoader = getForeignXLSLoader();
        TransformedLanguages languages = getLanguages(nativeXLSLoader,
                                                      foreignXLSLoader);

        vector<Language*>* similarGroups
                = groupSimilarNativeLangauges(languages.native);

        languages.native = similarGroups;

        PSOFactory psoFactory = getPSOFactory(languages.native,
                                              languages.foreign);
        PSO* pso = psoFactory.createPSO();

        Classifier *classifier = getClassifier(pso, languages);

        classifier->runClassification();
        delete classifier;
    }
/*
    vector<Language*>* groupSimilarNativeLangauges(vector<Language *> *native){

        Language* group0 = new Language((*native)[0]->getAlphabet());
        Language* group1 = new Language((*native)[0]->getAlphabet());
        Language* group2 = new Language((*native)[0]->getAlphabet());

        append(*group0, *((*native)[0]));
        append(*group0, *((*native)[6]));
        append(*group0, *((*native)[8]));

        logger::log("Group: 0, 6, 8");

        append(*group1, *((*native)[2]));
        append(*group1, *((*native)[3]));
        append(*group1, *((*native)[5]));

        logger::log("Group: 2, 3, 5");

        append(*group2, *((*native)[1]));
        append(*group2, *((*native)[4]));
        append(*group2, *((*native)[9]));
        append(*group2, *((*native)[7]));

        logger::log("Group: 1, 4, 9, 7");

        vector<Language*>* languages
                = new vector<Language*>{group0, group1, group2};

        return languages;
    }
*/
    vector<Language*>* groupSimilarNativeLangauges(vector<Language *> *native){

        Language* group0 = new Language((*native)[0]->getAlphabet());
        Language* group1 = new Language((*native)[0]->getAlphabet());

        append(*group0, *((*native)[0]));
        append(*group0, *((*native)[6]));
        append(*group0, *((*native)[8]));
        append(*group0, *((*native)[2]));
        append(*group0, *((*native)[3]));

        logger::log("Group: 0, 6, 8, 2, 3");

        append(*group1, *((*native)[5]));
        append(*group1, *((*native)[1]));
        append(*group1, *((*native)[4]));
        append(*group1, *((*native)[9]));
        append(*group1, *((*native)[7]));

        logger::log("Group: 5, 1, 4, 9, 7");

        vector<Language*>* languages
                = new vector<Language*>{group0, group1};

        return languages;
    }

    vector<Language*>* groupDisimilarNativeLangauges(
            vector<Language *> *native){

        Language* group0 = new Language((*native)[0]->getAlphabet());
        Language* group1 = new Language((*native)[0]->getAlphabet());
        Language* group2 = new Language((*native)[0]->getAlphabet());

        append(*group0, *((*native)[0]));
        append(*group0, *((*native)[4]));
        append(*group0, *((*native)[5]));

        logger::log("Group: 0, 4, 5");

        append(*group1, *((*native)[1]));
        append(*group1, *((*native)[2]));
        append(*group1, *((*native)[8]));

        logger::log("Group: 1, 2, 8");

        append(*group2, *((*native)[9]));
        append(*group2, *((*native)[7]));
        append(*group2, *((*native)[6]));
        append(*group2, *((*native)[3]));

        logger::log("Group: 9, 7, 6, 3");

        vector<Language*>* languages
                = new vector<Language*>{group0, group1, group2};

        return languages;
    }

    void append(Language& dist, Language& source){
        while(source.size() != 0){
            dist.addWord(source.stealLastWord());
        }
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
