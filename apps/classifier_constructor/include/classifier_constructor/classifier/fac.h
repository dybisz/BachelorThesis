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

    std::vector<Correspondence> correspondenceVector;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    FAC(DFA dfa);

    FAC(DFA dfa,
        std::vector<Correspondence> stateCorrespondence);


    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    void addCorrespondence(Correspondence stateCorrespondence);

    const DFA& getDFA() const;

    const std::vector<Correspondence>& getCorrespondence() const;

    const Label& classify(const Word& word) const;
};


#endif //BACHELOR_THESIS_CLASSIFIER_H
