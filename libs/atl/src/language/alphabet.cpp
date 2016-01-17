//
// Created by dybisz on 20.12.15.
//

#include <language/alphabet.h>
#include <stdexcept>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

Alphabet::Alphabet(const Alphabet& a) {
    _numberOfSymbols = a.getNumberOfSymbols();
    _produceSymbols();
    _produceIntervals();
}

Alphabet::Alphabet(int numberOfSymbols) : _numberOfSymbols(numberOfSymbols){
    _produceSymbols();
    _produceIntervals();
}

Alphabet::~Alphabet(){}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

Symbol Alphabet::convertToSymbol(double val) {
    int i = 0;

    for(; i < _intervals.size(); i++) {

        // If we deal with last symbol
        if(i == (_numberOfSymbols-1)) {
            if(_intervals[i].isInIntervalII(val)) break;
        }
        // Common symbol
        else {
            if(_intervals[i].isInIntervalIE(val)) break;
        }
    }

    // Return copy to prevent modifying alphabet
    return _symbols[i];
}

int Alphabet::size() const {
    return _symbols.size();
}

Symbol Alphabet::getSymbol(int i) const{
    return (_symbols[i]);
}

Interval Alphabet::getInterval(int i) const{
    return (_intervals[i]);
}

int Alphabet::getIndex(Symbol& symbol) const{
    return 1;
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

void Alphabet::_produceSymbols() {
    for(int i = 1; i <= _numberOfSymbols ;i++) {
        Symbol symbol(i);
        _symbols.push_back(symbol);
    }
}

void Alphabet::_produceIntervals() {
    for(int i = 0; i < _numberOfSymbols; i++) {
        Interval interval(i, _symbols[i].getVal());
        _intervals.push_back(interval);
    }
}

string Alphabet::toString() {
    string out = "";
    for(int i = 0 ; i < _numberOfSymbols ; i++) {
        out += "symb: ";
        out += _symbols[i].toString();
        out += " ";
        out += _intervals[i].toString();
        out += "\n";
    }
    return out;
}

int Alphabet::getNumberOfSymbols() const{
    return _numberOfSymbols;
}

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */

Symbol Alphabet::operator[](int i) {
    return this->getSymbol(i);
}

Interval Alphabet::operator()(int i)
{
    return this->getInterval(i);
}


bool Alphabet::operator == (const Alphabet &b) const {
    if(this->size() != b.size()) {
        throw invalid_argument( "Alphabets sizes do not match.");
    }

    bool letterFound = false;

    for(int i = 0; i < this->size(); i++) {
        for(int j = 0 ; j < b.size() ; j++) {
            if(_symbols[i] == (b.getSymbol(j))){
                letterFound = true;
                break;
            }
        }
        if(!letterFound) break;
    }

    return letterFound;
}


