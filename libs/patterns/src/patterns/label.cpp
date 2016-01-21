//
// Created by jakub on 1/20/16.
//

#include "patterns/label.h"

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Label::Label(int value) : value(value){

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

int Label::getValue() const {
    return this->value;
}

bool Label::operator==(const Label& label) const{
    return (this->value == label.value);
}
