//
// Created by jakub on 1/24/16.
//

#ifndef BACHELOR_THESIS_CFAC_BUILDER_H
#define BACHELOR_THESIS_CFAC_BUILDER_H


#include <classifier_constructor/classifier/cfac.h>
#include <class.h>
#include <language/language.h>
#include <classifier_constructor/experiments/classification/pso_factory.h>

/**
 *  CFACBuilder is used to build the CFAC classifier.
 *  As input it takes Native and Foreign classes.
 *
 *  1) Classes are Transformed to Languages
 *      a) If build() have been called the alphabet size is chosen
 *      dynamically based on Transformation Analysis.
 *
 *      b) If build(int alphabetSize) is called then the alphabetSize is
 *      used instead.
 *
 *  2) Each Native Language, a corresponding FAC is created and thus requires:
 *      a) Contructed DFA by the PSO heuristics
 *      b) Correspondence of Labels and States (each language is a label).
 *
 ****************************************************************************
 *
 *
 */
class CFACBuilder {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    const int FOREIGN_LABEL_VALUE = -1;

    // The constructed classifier
    CFAC* classifier;

    // Classes
    std::vector<Language*>* nativeLanguages;
    std::vector<Language*>* foreignLanguages;

    // Number of states per native class
    int statesPerNative;
    // Number of states per foreign class.
    int statesPerForeign;

    PSOFactory* psoFactory;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    /*
     * Builds all required FAC classifiers and return them as vector
     */
    std::vector<FAC> buildFACClassifiers(
            std::vector<Language*>* nativeLanguages,
            std::vector<Language*>* foreignLanguages,
            int alphabetSize);

    /*
     * Builds a binary FAC: native language vs foreing languages.
     * nativeLabel represents the label of nativeLanguage.
     * foreignLabel represents label of all foreign languages.
     */
    FAC buildBinaryFAC(Language* nativeLanguage,
                       Label nativeLabel,
                       Language* foreignLanguage,
                       Label foreignLabel,
                       int alphabetSize);

    /*
     * Creates correspondence of native language with nativeLabel
     * and foreign languages with foreign label based on their existing
     * state correspondences.
     */
    Correspondence createCorrespondece(Language* nativeLanguage,
                                       Label nativeLabel,
                                       Language* foreignLanguages,
                                       Label foreignLabel);
    /*
     * Computes the alphabet size using the TransformationAnanlyzer
     */
    int computeAlphabetSize(std::vector<Class *>* nativeClasses);

public:

    const Label FOREIGN_LABEL;

    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    CFACBuilder(std::vector<Language*>* nativeLanguages,
                std::vector<Language*>* foreignLanguages,
                int statesPerNative,
                int statesPerForeign,
                PSOFactory* psoFactory);

    ~CFACBuilder();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    /*
     * Starts building the classifier.
     * The alphabet size is chosen dynamically by transformation analyzer.
     */
    void build();

    /*
     * Builds the classifier on specific alphabet size
     */
    void build(int alphabetSize);

    const CFAC& getClassifier() const;
};


#endif //BACHELOR_THESIS_CFAC_BUILDER_H
