//
// Created by dybisz on 17.12.15.
//

#ifndef BACHELOR_THESIS_FEATURE_VECTOR_H
#define BACHELOR_THESIS_FEATURE_VECTOR_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include "symbol.h"

using namespace std;

/**
 * There is only one reason for this class: manipulating features stored in
 * the vector.
 */
class FeatureVector{
public:

    // Feature vector can be created either from provided vectors of integers,
    // Symbol class objects, pointers to Symbol class objects or empty.
    FeatureVector();
    FeatureVector(const vector<int> &entries);
    FeatureVector(const vector<Symbol> &entries);
    FeatureVector(const vector<Symbol*> &entries);

    // Entries of the vector are pointers to Symbol class, hence all must
    // be handled when vector is being destroyed.
    ~FeatureVector();

    // Instead of using operators, one can explicitly call one of the
    // following methods to append symbols. First one will create object
    // of Symbol class, which is very convenient when it comes to pointers.
    // Second one will work on created pointer to Symbol class and destroy
    // it after work isi finished, hence no outside deletion is needed.
    void appendSymbol(int symbol);
    void appendSymbol(Symbol* symbol);

    // Auxiliary methids, which definition is selfexplanatory regarding
    // their names.
    int size() const;
    string toString() const;
    Symbol* getSymbol(int i) const;

    // Overloaded operators and their purpose:
    // 1) []    accessing i'th symbol in the vector. Returns pointer to
    //          Symbol class, to avoid inefficient copying.
    // 2) ()    accessing value of i'th symbol in the vector. It might be
    //          useful e.g. when simple checking is needed instead of
    //          operations on Symbol object.
    // 3) +     appends symbol at the end of the vector. It is more compact
    //          than explicitly calling appendSymbol(). Two versions:
    //          with int and Symbol*, provides flexibility.
    // 4) ==    Compares entries of two feature vectors and if the are the
    //          same returns true, otherwise false is returned.
    Symbol* operator[](int i);
    int operator()(int i);
    void operator+(const int& a);
    void operator+(Symbol* a);
    bool operator == (const FeatureVector &b) const;

private:
    vector<Symbol*> _entries;
};


#endif //BACHELOR_THESIS_FEATURE_VECTOR_H
