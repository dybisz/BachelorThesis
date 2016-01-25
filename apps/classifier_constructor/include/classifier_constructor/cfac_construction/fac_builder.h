//
// Created by jakub on 1/24/16.
//

#ifndef BACHELOR_THESIS_FAC_BUILDER_H
#define BACHELOR_THESIS_FAC_BUILDER_H


#include <classifier_constructor/classifier/fac.h>
#include <language/language.h>
#include <classifier_constructor/pso_classifier/pso_factory.h>

class FACBuilder {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    FAC* classifier;

    Correspondence correspondence;

    PSO* pso;

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    FACBuilder(Correspondence correspondence,
               PSO* pso);

    ~FACBuilder();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    void build();

    const FAC& getClassifier();
};


#endif //BACHELOR_THESIS_FAC_BUILDER_H
