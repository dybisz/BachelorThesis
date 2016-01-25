//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_CLASSIFIER_H
#define BACHELOR_THESIS_CLASSIFIER_H

#include <automata/dfa.h>
#include <classifier_constructor/classifier/correspondence/correspondence.h>

/*
 * Finite Automata Classifier.
 * Contains:
 *      - DFA which compute a word and outputs a state.
 *      - Correspondence of labels to states.
 *
 */
class FAC {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    DFA dfa;

    Correspondence correspondence;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    FAC(DFA dfa, Correspondence correspondence);

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    const DFA& getDFA() const;

    const Correspondence& getCorrespondence() const;

    const Label& classify(Word& word) const;
};


#endif //BACHELOR_THESIS_CLASSIFIER_H
