//
// Created by jakub on 1/25/16.
//

#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_quality.h>
#include "classifier_constructor/experiments/common.h"

using namespace transformation;

XlsLoader experiments::getNativeXLSLoader() {
    XlsLoader nativeXLSLoader(settings::NATIVE_XLS_PATH,
                              settings::NUMBER_OF_CLASSES,
                              settings::PATTERNS_PER_CLASS);
    return nativeXLSLoader;
}

XlsLoader experiments::getForeignXLSLoader() {
    XlsLoader foreignXLSLoader(settings::FOREIGN_XLS_PATH,
                               settings::NUMBER_OF_CLASSES,
                               settings::PATTERNS_PER_CLASS);
    return foreignXLSLoader;
}

TransformedLanguages experiments::getLanguages(XlsLoader& nativeXLSLoader,
                                               XlsLoader& foreignXLSLoader){
    std::vector<Class *> *nativeClasses = nativeXLSLoader.getClasses();
    std::vector<Class *> *foreignClasses = foreignXLSLoader.getClasses();

    TransformationClasses classes(nativeClasses, foreignClasses);
    TransformedLanguages languages = transform(classes,
                                               settings::ALPHABET_SIZE);
    // Needed for DFA compute to match word indexing from 0
    quality::_convertWords(languages.native);
    quality::_convertWords(languages.foreign);
    return languages;
}
