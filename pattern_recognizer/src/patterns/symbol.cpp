//
// Created by dybisz on 17.12.15.
//

#include <symbol.h>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

Symbol::Symbol(int val) : _val(val) {}
Symbol::Symbol(const Symbol& s): _val(s.getVal()) {}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

int Symbol::getVal() const{
    return _val;
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */

bool Symbol::operator==(const Symbol &b) const
{
    return (this->getVal() == b.getVal() );
}

bool Symbol::operator == (const int &b) const {
    return (this->getVal() == b);
}