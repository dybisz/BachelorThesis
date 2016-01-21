//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_CLASSIFIER_H
#define BACHELOR_THESIS_CLASSIFIER_H


#include <automata/dfa.h>
#include <classifier_constructor/classifier/correspondence/correspondence.h>

class FACClassifier {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    DFA dfa;

    std::vector<Correspondence> stateCorrespondenceVector;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    FACClassifier(DFA dfa);

    FACClassifier(DFA dfa,
                  std::vector<Correspondence> stateCorrespondence);


    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    void addStateCorrespondence(Correspondence stateCorrespondence);

    const DFA& getDFA() const;

    const std::vector<Correspondence>& getStateCorrespondence() const;

    const Label& classify(const Word& word) const;
};


#endif //BACHELOR_THESIS_CLASSIFIER_H
