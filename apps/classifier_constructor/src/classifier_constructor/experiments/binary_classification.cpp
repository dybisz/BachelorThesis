//
// Created by jakub on 1/24/16.
//

#include "classifier_constructor/experiments/binary_classification.h"

#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_constructor/settings/pso_settings.h>
#include <classifier_constructor/settings/thread_settings.h>

#include <sstream>
#include <logger/log.h>
#include <transformation/sets_disassociation.h>
#include <classifier_constructor/experiments/common.h>

using namespace experiments;
using namespace transformation;

void binary_experiment::runBinaryClassification() {
    PSOFactory psoFactory = getPSOFactory();
    XlsLoader nativeXLSLoader = getNativeXLSLoader();
    XlsLoader foreignXLSLoader = getForeignXLSLoader();
    TransformedLanguages languages = getLanguages(nativeXLSLoader,
                                                  foreignXLSLoader);
    std::vector<Language*>* nativeTestLanguages
            = set_disassociation::detachWords(settings::TESTING_SET_RATIO,
                                              languages.native);
    std::vector<Language*>* foreignTestLanguages
            = set_disassociation::detachWords(settings::TESTING_SET_RATIO,
                                              languages.foreign);

    CFACBuilder cfacBuilder(languages.native, languages.foreign,
                            settings::STATES_PER_NATIVE,
                            settings::STATES_PER_FOREIGN,
                            &psoFactory);
    cfacBuilder.build(settings::ALPHABET_SIZE);
    CFAC cfac = cfacBuilder.getClassifier();

    ConfusionMatrix qualityResults = runQualityCheck(cfac,
                                                     nativeTestLanguages,
                                                     foreignTestLanguages,
                                                     cfacBuilder.FOREIGN_LABEL);
    string plotStr = confusionMatrixLatexTable(qualityResults);
    logger::log(File("QualityCheck.txt", false), plotStr);

    transformation::deleteLanguages(languages.native);
    transformation::deleteLanguages(nativeTestLanguages);
    transformation::deleteLanguages(languages.foreign);
    transformation::deleteLanguages(foreignTestLanguages);
}

PSOFactory binary_experiment::getPSOFactory() {
    PSOFactory psoFactory(
            settings::SWARM_SIZE, settings::MAX_ITER,
            settings::TRUE_THREAD_COUNT, settings::MAX_VELOCITY,
            settings::ENCODING_DELTA, settings::UPPER_BOUND_ERR,
            settings::LEARNING_FACTOR, settings::PARTICLE_VEL_WEIGHT
    );
    return psoFactory;
}

binary_experiment::ConfusionMatrix binary_experiment::runQualityCheck(
        const CFAC &cfac,
        std::vector<Language*>* nativeLanguages,
        std::vector<Language*>* foreignLanguages,
        const Label& foreignLabel) {
    const vector<FAC> facs = cfac.getClassifiers();

    vector<vector<double>> results;
    for(unsigned int i = 0; i < nativeLanguages->size(); i++){
        vector<double> languageResults;
        Language* language = ((*nativeLanguages)[i]);
        for(unsigned int j = 0; j < facs.size(); j++){
            double ratio = classifiedToNativeRatio(*language,
                                                   facs[j],
                                                   foreignLabel);
            languageResults.push_back(ratio);

            string info = "L" + to_string(i) + " vs L" + to_string(j);
            logger::log(info, " = ", ratio);
        }
        results.push_back(languageResults);
    }
    ConfusionMatrix qualityResults(results);

    return qualityResults;
}

string binary_experiment::confusionMatrixLatexTable(
        const binary_experiment::ConfusionMatrix &qualityResults) {
    vector<vector<double>> results = qualityResults.results;

    string SYMBOL_SEPERATOR = "&";
    string ROW_SEPERATOR = "\\\\ \n \\hline \n";

    stringstream ss;
    int FLOAT_PRINT_PRECISION = 2;
    ss << setprecision(FLOAT_PRINT_PRECISION);

    int languageCount = results.size();

    for(unsigned int i = 0; i < languageCount; i++){
        vector<double> languageResults = results[i];
        for(unsigned int j = 0; j < languageResults.size(); j++){
            ss << SYMBOL_SEPERATOR << languageResults[j];
        }
        ss << ROW_SEPERATOR;
    }
    ss << ROW_SEPERATOR;

    return ss.str();
}

double binary_experiment::classifiedToNativeRatio(const Language &language,
                                                  const FAC &fac,
                                                  const Label &foreignLabel) {
    unsigned int classifiedToNativeCount = 0;
    unsigned int size = language.size();

    for(unsigned int i = 0; i < size; i++){
        Word* word = language.getWord(i);

        Label classifiedLabel = fac.classify(*word);
        if(!(classifiedLabel == foreignLabel)){
            classifiedToNativeCount++;
        }
    }
    double ratio = (double)classifiedToNativeCount/size;

    return ratio;
}