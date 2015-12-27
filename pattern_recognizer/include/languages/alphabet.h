//
// Created by dybisz on 20.12.15.
//

#ifndef BACHELOR_THESIS_ALPHABET_H
#define BACHELOR_THESIS_ALPHABET_H

#include <interval.h>
#include <vector>
#include <iostream>
#include "symbol.h"

using namespace std;

/*
 * Wraps up set of methods to manipulate vector of symbols. Each symbol has
 * a corresponding interval. It is mainly used for pattern-to-language
 * conversion.
 */
class Alphabet {
public:
    Alphabet(const Alphabet& other);
    Alphabet(int numberOfSymbols);
    ~Alphabet();

    // Because alphabet knows symbol-interval relation, it can tells outside
    // user which symbol corresponds to provided value.
    Symbol convertToSymbol(double val);

    // Auxiliary methods, which definition is selfexplanatory regarding
    // their names.
    int size() const;
    Symbol getSymbol(int i) const;
    Interval getInterval(int i) const;
    string toString();
    int getNumberOfSymbols() const;

    // Overloaded operators and their purpose:
    // 1) []    accessing i'th symbol in the alphabet. Returns pointer to
    //          Symbol class, to avoid inefficient copying.
    // 2) ()    accessing i'th interval (which corresponds to i'th symbol).
    //          Returns pointer to Symbol class, to avoid inefficient copying.
    // 4) ==    Compares two alphabets in terms of contained symbols.
    Symbol operator[](int i);
    Interval operator()(int i);
    bool operator == (const Alphabet &b) const;
    int getIndex(Symbol& symbol) const;

private:
    int _numberOfSymbols;
    vector<Interval> _intervals;
    vector<Symbol> _symbols;

    // Symbols are produced based on integers from interval <1;#symbols>
    // Intervals are of form: <0 ; symb_1) u < 1 ; symb_2) u ...
    // u <#symbols -1 ; #symbols>
    void _produceSymbols();
    void _produceIntervals();

};

#endif //BACHELOR_THESIS_ALPHABET_H
