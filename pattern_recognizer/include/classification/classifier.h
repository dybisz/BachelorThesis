//
// Created by jakub on 12/22/15.
//

#ifndef BACHELOR_THESIS_CLASSIFICATOR_H
#define BACHELOR_THESIS_CLASSIFICATOR_H

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
 */
class Classifier {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    // Set of native languages
    std::vector<Language*>* _nativeLanguages;
    // Set of foreign languages
    std::vector<Language*>* _foreignLanguages;

    std::vector<Language*>* _nativeTestingSet;
    std::vector<Language*>* _foreignTestingSet;

    // Used to run PSO
    unsigned int _numberOfStates;
    unsigned int _alphabetSize;

    // Number of states correspodence per native language
    unsigned int _statesPerNative;
    // Number of states correspodence per foreign language
    unsigned int _statesPerForeign;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

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

    /*
     * Takes care of deleting the memory of all languages
     */
    ~Classifier();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    void runClassification();
};


#endif //BACHELOR_THESIS_CLASSIFICATOR_H
