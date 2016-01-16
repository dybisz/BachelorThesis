//
// Created by jakub on 12/22/15.
//

#ifndef BACHELOR_THESIS_CLASSIFICATOR_H
#define BACHELOR_THESIS_CLASSIFICATOR_H

#include <pso/pso_t.h>
#include "dfa.h"
#include "language.h"

/*
 * Classifier is the main class of classification process.
 * It takes all transformed languages and select the state correspondence.
 * It runs PSO and calculate quality of the classifier.
 *
 * Recall that PSO requires number of states and number of symbols.
 * Number of symbols is given by alphabet size - chosen by user.
 * Number of states depends on:
 *      - The number of native languages and their state correspondence.
 *      - Foreign language and their state correspondence.
 *          Foreign language might represent some specific pattern but
 *          all foreign languages are considered to be one big language.
 *
 * Classifier takes ownership over PSO
 */
class Classifier {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    pso::PSO_T* pso;

    // Set of native languages
    std::vector<Language*>* _nativeLanguages;
    // Set of foreign languages
    std::vector<Language*>* _foreignLanguages;

    std::vector<Language*>* _nativeTestingSet;
    std::vector<Language*>* _foreignTestingSet;

    // Used to run PSO
    unsigned int _numberOfStates;
    unsigned int _alphabetSize;

    // Number of states correspondence per native language
    unsigned int _statesPerNative;
    // Number of states correspondence per foreign language
    unsigned int _statesPerForeign;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    /*
     * Calculates and prints quality results of the classifier.
     */
    void _calculateAndPrintQualityResults(const DFA* bestDFA);

    /*
     * Prints info about state correspondence and the languages
     */
    void _printStateCorrespondence();

    /*
     * Prints out information about sizes of provided languages/sets.
     */
    void _printSetInfo(std::vector<Language *> *pLanguages,
                        std::string setName);

    /*
     * Calculate and save number of states
     */
    unsigned int _calculateAndSetNumberOfStates();

public:
    Classifier(std::vector<Language*>* nativeLanguages,
                std::vector<Language*>* foreignLanguages,
                unsigned int statesPerNative,
                unsigned int statesPerForeign,
                unsigned int alphabetSize);

    Classifier(std::vector<Language*>* nativeLanguages,
                std::vector<Language*>* foreignLanguages,
                unsigned int statesPerNative,
                unsigned int statesPerForeign,
                unsigned int alphabetSize,
                double testingSetRatio);

    Classifier(pso::PSO_T* pso,
               std::vector<Language*>* nativeLanguages,
               std::vector<Language*>* foreignLanguages,
               unsigned int statesPerNative,
               unsigned int statesPerForeign,
               unsigned int alphabetSize,
               double testingSetRatio);
    /*
     * Takes care of deleting the memory of all languages
     */
    ~Classifier();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    void runClassification();

    void runClassificationNew();

    unsigned int getStateCount() const;

    const std::vector<Language*>* getNativeTrainingLanguages() const;
    const std::vector<Language*>* getNativeTestingLanguages() const;
    const std::vector<Language*>* getForeignLanguages() const;

};


#endif //BACHELOR_THESIS_CLASSIFICATOR_H
