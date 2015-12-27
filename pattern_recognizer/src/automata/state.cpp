//
// Created by dybisz on 19.12.15.
//

#include <state.h>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

State::State(int val) : _val(val) {}
State::State(const State& s): _val(s.getVal()) {}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

int State::getVal() const{
    return _val;
}

string State::toString() const{
    return to_string(_val);
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */

bool State::operator==(const State &b) const
{
    return (this->getVal() == b.getVal() );
}

bool State::operator == (const int &b) const {
    return (this->getVal() == b);
}

bool State::operator!=(const State &b) const{
    return !(*this == b);
}