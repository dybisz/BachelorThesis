//
// Created by jakub on 1/24/16.
//

#ifndef BACHELOR_THESIS_BINARY_CLASSIFICATION_H
#define BACHELOR_THESIS_BINARY_CLASSIFICATION_H

#include <classifier_constructor/classifier/cfac.h>
#include <class.h>
#include <language/language.h>
#include <classifier_constructor/experiments/classification/pso_factory.h>
#include <xls_loader.h>
#include <classifier_constructor/cfac_construction/cfac_builder.h>

/**
 * Binary Classification experiment tests the behaviour of
 * Composite Finite Automata Classifier when each of FACs are binary
 * classifiers: Native vs Foreign. Each FAC corresponds
 * to different native class.
 *
 * The experiments are based on the settings from the application.
 */
namespace experiments {

    struct ConfusionMatrix {
        vector<vector<double>> results;

        ConfusionMatrix(vector<vector<double>> results){
            this->results = results;
        }
    };

    /*
     * Begins the classification experiments
     */
    void runBinaryClassification();

    PSOFactory getPSOFactory();

    XlsLoader getNativeXLSLoader();
    XlsLoader getForeignXLSLoader();

    vector<Language*>* getNativeLanguages(XlsLoader& nativeLoader);
    vector<Language*>* getForeignLanguages(XlsLoader& foreignLoader);

    /*
     * Runs quality check of the constructed classifier.
     * For each native language checks how many times words have been
     * classified to native classes.
     * Each such native language will correspond to a vector of ratios of
     * classified words count to all words count of that language.
     *
     * The result is a confusion matrix.
     */
    ConfusionMatrix runQualityCheck(const CFAC &cfac,
                                    std::vector<Language*>* nativeLanguages,
                                    std::vector<Language*>* foreignLanguages,
                                    const Label& foreignLabel);

    /*
     * Plots the confusion matrix.
     */
    string confusionMatrixLatexTable(const ConfusionMatrix &qualityResults);

    /*
     * Computes how many words have been classified to a native class by
     * the FAC
     */
    double classifiedToNativeRatio(const Language &language,
                                   const FAC &fac,
                                   const Label &foreignLabel);

}

#endif //BACHELOR_THESIS_BINARY_CLASSIFICATION_H
