//
// Created by dybisz on 17.12.15.
//

#include "feature_vector.h"

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

FeatureVector::FeatureVector() {}

FeatureVector::FeatureVector(const vector<int> &entries) {
    for(auto it = entries.begin(); it != entries.end(); ++it) {
        Symbol* symbol = new Symbol(*it);
        _entries.push_back(symbol);
    }
}

FeatureVector::FeatureVector(const vector<Symbol> &entries) {
    for(auto it = entries.begin(); it != entries.end(); ++it) {
        Symbol* symbol = new Symbol(*it);
        _entries.push_back(symbol);
    }
}

FeatureVector::FeatureVector(const vector<Symbol*> &entries) {
    for(auto it = entries.begin(); it != entries.end(); ++it) {
        _entries.push_back(*it);
    }
}

FeatureVector::~FeatureVector() {
    for (auto it = _entries.begin() ; it != _entries.end(); ++it)
    {
        delete (*it);
    }
    _entries.clear();
}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

void FeatureVector::appendSymbol(int symbol) {
    Symbol* a = new Symbol(symbol);
    _entries.push_back(a);
}

void FeatureVector::appendSymbol(Symbol* symbol) {
    _entries.push_back(symbol);
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

int FeatureVector::size() const{
    return _entries.size();
}

string FeatureVector::toString() const{
    string out = "";
    for (auto it = _entries.begin() ; it != _entries.end(); ++it)
    {
        out += to_string(((*it)->getVal()));
    }
    return out;
}

Symbol* FeatureVector::getSymbol(int i) const {
    return _entries[i];
}

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */

Symbol* FeatureVector::operator[](int i) {
    return _entries[i];
}

int FeatureVector::operator()(int i)
{
    return _entries[i]->getVal();
}

void FeatureVector::operator+(const int& a)
{
    this->appendSymbol(a);
}

void FeatureVector::operator+(Symbol* a) {
    this->appendSymbol(a);
}

bool FeatureVector::operator == (const FeatureVector &b) const {
    if(this->size() != b.size()) {
        throw invalid_argument( "Feature vectors sizes do not match.");
    }

    bool areTheSame = true;

    for(int i = 0; i < this->size(); i++) {
        if(_entries[i]->getVal() != b.getSymbol(i)->getVal()){
            areTheSame = false;
            break;
        }
    }

    return areTheSame;
}