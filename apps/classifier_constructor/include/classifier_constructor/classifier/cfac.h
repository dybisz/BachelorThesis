//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_FAC_H
#define BACHELOR_THESIS_FAC_H

#include "fac.h"

/**
 * Composite Finite Automata Classifier
 */
class CFAC {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    std::vector<FAC> facClassifiers;

    int alphabetSize;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    CFAC(std::vector<FAC> facClassifiers, int alphabetSize);

    ~CFAC();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    const std::vector<FAC>& getClassifiers() const;

    int getAlphabetSize() const;

    const Label& classify(const Word& word) const;
};


#endif //BACHELOR_THESIS_FAC_H
