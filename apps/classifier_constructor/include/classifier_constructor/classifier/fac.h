//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_FAC_H
#define BACHELOR_THESIS_FAC_H

#include "classifier_constructor/classifier/fac_classifier.h"

/**
 * Finite Automata Classifier
 */
class FAC {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    std::vector<FACClassifier> facClassifiers;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    FAC();

    ~FAC();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    const std::vector<FACClassifier>& getClassifiers() const;

    const Label& classify(const Word& word) const;
};


#endif //BACHELOR_THESIS_FAC_H
