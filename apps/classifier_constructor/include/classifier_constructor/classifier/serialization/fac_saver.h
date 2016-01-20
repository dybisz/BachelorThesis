//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_FACSAVER_H
#define BACHELOR_THESIS_FACSAVER_H


#include <classifier_constructor/classifier/fac.h>

/**
 * FAC Saver saves FAC Classifier to hard disk memory.
 *
 * The classifier is stored in a directory.
 * The main directory contains
 * sub directories - possibly many - each contains DFAC Classifier.
 * Each DFAC Classifier contains:
 *      Saved DFA.
 *      State Correspondence.
 *
 */
class FACSaver {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    const std::string STATE_CORRES_EXT = ".sc";

    const std::string DEFAULT_DFA_NAME = "automaton";
    const std::string DEFAULT_STATE_CORRES_NAME = "states_corres";

    const FAC* classifier;

    // Path where the classifier should be saved
    std::string dirPath;

    // Name of the main directory
    std::string dirName;

    // Full path to the main directory
    std::string dirFullPath;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

    void createMainDir();

    void saveSubClassifier(const FACClassifier& subClassifier, int id);

    void saveDFA(const DFA& dfa, std::string path);

    void saveStateCorrespondence(const StateCorrespondence& stateCorrespondence,
                                 std::string path);

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    FACSaver(const FAC* classifier,
             std::string dirPath, std::string dirName);

    ~FACSaver();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    void save();

};


#endif //BACHELOR_THESIS_FACSAVER_H
