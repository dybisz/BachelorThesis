//
// Created by jakub on 12/22/15.
//

#ifndef BACHELOR_THESIS_CLASSIFICATOR_H
#define BACHELOR_THESIS_CLASSIFICATOR_H

#include <pso/pso.h>
#include <automata/dfa.h>
#include <language/language.h>

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

    pso::PSO* pso;

    // Set of native languages
    std::vector<Language*>* _nativeLanguages;
    // Set of foreign languages
    std::vector<Language*>* _foreignLanguages;

    const DFA* classifierDFA;

public:

    Classifier(pso::PSO * pso,
               std::vector<Language*>* nativeLanguages,
               std::vector<Language*>* foreignLanguages);
    /*
     * Takes care of deleting the memory of all languages
     */
    ~Classifier();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    void runClassification();

    const DFA& getClassiferDFA() const;

};


#endif //BACHELOR_THESIS_CLASSIFICATOR_H
