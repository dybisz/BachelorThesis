//
// Created by dybisz on 17.12.15.
//

#include <language/word.h>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

Word::Word() {}

Word::Word(const Word* w) {
    for(int i = 0; i < w->size(); ++i) {
        Symbol* symbol = new Symbol(w->getSymbol(i)->getVal());
        _entries.push_back(symbol);
    }
}

Word::Word(const int entries[], int n) {
    for(int i = 0; i < n ; i++) {
        Symbol* symbol = new Symbol(entries[i]);
        _entries.push_back(symbol);
    }
}

Word::Word(const vector<int> &entries) {
    for(auto it = entries.begin(); it != entries.end(); ++it) {
        Symbol* symbol = new Symbol(*it);
        _entries.push_back(symbol);
    }
}

Word::Word(const vector<Symbol> &entries) {
    for(auto it = entries.begin(); it != entries.end(); ++it) {
        Symbol* symbol = new Symbol(*it);
        _entries.push_back(symbol);
    }
}

Word::Word(const vector<Symbol*> &entries) {
    for(auto it = entries.begin(); it != entries.end(); ++it) {
        _entries.push_back(*it);
    }
}

Word::~Word() {
    for (auto it = _entries.begin() ; it != _entries.end(); ++it)
    {
        delete (*it);
    }
    _entries.clear();
}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

void Word::appendSymbol(int symbol) {
    Symbol* a = new Symbol(symbol);
    _entries.push_back(a);
}

void Word::appendSymbol(Symbol* symbol) {
    _entries.push_back(symbol);
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

int Word::size() const{
    return _entries.size();
}

string Word::toString() const{
    string out = "";
    for (auto it = _entries.begin() ; it != _entries.end(); ++it)
    {
        out += to_string(((*it)->getVal()));
        out += " ";
    }
    return out;
}

Symbol*Word::getSymbol(int i) const {
    return _entries[i];
}

void Word::clear() {
    for (auto it = _entries.begin() ; it != _entries.end(); ++it)
    {
        delete (*it);
    }
    _entries.clear();
}

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */

Symbol*Word::operator[](int i) {
    if (size() < 1) {
        throw invalid_argument("size of word is < 1");
    }

    return _entries[i];
}

int Word::operator()(int i)
{
    if (size() < 1) {
        throw invalid_argument("size of word is < 1");
    }

    return _entries[i]->getVal();
}

void Word::operator+(const int& a)
{
    this->appendSymbol(a);
}

void Word::operator+(Symbol* a) {
    this->appendSymbol(a);
}

bool Word::operator == (const Word &b) const {
    if(this->size() != b.size()) {
        throw invalid_argument( "Word sizes do not match.");
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