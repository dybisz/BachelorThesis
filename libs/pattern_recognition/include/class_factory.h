//
// Created by jakub on 2/4/16.
//

#ifndef BACHELOR_THESIS_CLASSFACTORY_H
#define BACHELOR_THESIS_CLASSFACTORY_H


#include "class.h"


class ClassFactory {
private:
    //-----------------------------------------------------------//
    //  PRIVATE FIELDS
    //-----------------------------------------------------------//

    //-----------------------------------------------------------//
    //  PRIVATE METHODS
    //-----------------------------------------------------------//

public:
    //-----------------------------------------------------------//
    //  CONSTRUCTORS
    //-----------------------------------------------------------//

    ClassFactory();

    ~ClassFactory();

    //-----------------------------------------------------------//
    //  PUBLIC METHODS
    //-----------------------------------------------------------//

    std::vector<Class*>* generateRandomClasses
};


#endif //BACHELOR_THESIS_CLASSFACTORY_H
