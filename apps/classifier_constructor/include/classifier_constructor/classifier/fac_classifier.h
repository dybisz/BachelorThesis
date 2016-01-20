//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_CLASSIFIER_H
#define BACHELOR_THESIS_CLASSIFIER_H


#include <automata/dfa.h>
#include "classifier_constructor/classifier/state_correspondence.h"

class FACClassifier {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    DFA dfa;

    std::vector<StateCorrespondence> stateCorrespondenceVector;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    FACClassifier(DFA dfa);

    FACClassifier(DFA dfa,
                  std::vector<StateCorrespondence> stateCorrespondence);


    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    void addStateCorrespondence(StateCorrespondence stateCorrespondence);

    const DFA& getDFA() const;

    const std::vector<StateCorrespondence>& getStateCorrespondence() const;

    const Label& classify(const Word& word) const;
};


#endif //BACHELOR_THESIS_CLASSIFIER_H
