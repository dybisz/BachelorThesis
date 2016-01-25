//
// Created by jakub on 1/24/16.
//

#include <classifier_constructor/pso_classifier/pso_factory.h>

#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_constructor/settings/pso_settings.h>
#include <classifier_constructor/settings/thread_settings.h>

#include <xls_loader.h>
#include <classifier_constructor/cfac_construction/cfac_builder.h>
#include <sstream>
#include <logger/log.h>
#include <transformation/sets_disassociation.h>
#include <classifier_quality.h>
#include <transformation/transformation.h>
#include "classifier_constructor/cfac_construction/construction.h"

void constructCFAC() {
    PSOFactory psoFactory(
            settings::SWARM_SIZE, settings::MAX_ITER,
            settings::TRUE_THREAD_COUNT, settings::MAX_VELOCITY,
            settings::ENCODING_DELTA, settings::UPPER_BOUND_ERR,
            settings::LEARNING_FACTOR, settings::PARTICLE_VEL_WEIGHT
    );

    XlsLoader nativeXLSLoader(settings::NATIVE_XLS_PATH,
                              settings::NUMBER_OF_CLASSES,
                              settings::PATTERNS_PER_CLASS);
    XlsLoader foreignXLSLoader(settings::FOREIGN_XLS_PATH,
                               settings::NUMBER_OF_CLASSES,
                               settings::PATTERNS_PER_CLASS);

    std::vector<Class *>* nativeClasses = nativeXLSLoader.getClasses();
    std::vector<Class *>* foreignClasses = foreignXLSLoader.getClasses();

    vector<Language*>* nativeLanguages
            = transformation::transform(nativeClasses, settings::ALPHABET_SIZE);
    vector<Language*>* foreignLanguages
            = transformation::transform(foreignClasses, settings::ALPHABET_SIZE);
    quality::_convertWords(nativeLanguages);
    quality::_convertWords(foreignLanguages);

    std::vector<Language*>* nativeTestLanguages
            = set_disassociation::detachWords(settings::TESTING_SET_RATIO,
                                              nativeLanguages);
    std::vector<Language*>* foreignTestLanguages
            = set_disassociation::detachWords(settings::TESTING_SET_RATIO,
                                              foreignLanguages);

    CFACBuilder cfacBuilder(nativeLanguages,
                            foreignLanguages,
                            settings::STATES_PER_NATIVE,
                            settings::STATES_PER_FOREIGN,
                            &psoFactory);
    cfacBuilder.build(settings::ALPHABET_SIZE);

    stringstream ss;

    const CFAC& cfac = cfacBuilder.getClassifier();
    const vector<FAC>& facs = cfac.getClassifiers();
    for(unsigned int i = 0; i < facs.size(); i++){
        ss << "FAC(" << i << ")" << std::endl;
        ss << facs[i].getCorrespondence();
    }

    logger::log(ss.str());
}
