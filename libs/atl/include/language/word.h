//
// Created by dybisz on 17.12.15.
//

#ifndef BACHELOR_THESIS_FEATURE_VECTOR_H
#define BACHELOR_THESIS_FEATURE_VECTOR_H

#include <vector>
#include <string>
#include <iostream>
#include <stdexcept>
#include "language/symbol.h"

using namespace std;

/*
 * Created mainly for abstraction level maintaining. It allows user to
 * access and manipulate word representation in a convenient way.
 *
 * Ownership:
 *      Symbols
 */
class Word {
public:

    // Feature vector can be created:
    // 1) Empty.
    // 2) Copy entries from provided Word's pointer.
    // 3) From provided vectors of integers - WARNING: copy will be created
    // 4) From vector of Symbol class objects
    // 5) From vector of pointers to Symbol class objects
    Word();
    Word(const Word* w);
    Word(const int entries[], int length);
    Word(const vector<int> &entries);
    Word(const vector<Symbol> &entries);
    Word(const vector<Symbol*> &entries);

    // Entries of the vector are pointers to Symbol class, hence all must
    // be handled when vector is being destroyed.
    ~Word();

    // Instead of using operators, one can explicitly call one of the
    // following methods to append symbols. First one will create object
    // of Symbol class, which is very convenient when it comes to pointers.
    // Second one will work on created pointer to Symbol class and destroy
    // it after work isi finished, hence no outside deletion is needed.
    void appendSymbol(int symbol);
    void appendSymbol(Symbol* symbol);

    // Auxiliary methods, which definition is selfexplanatory regarding
    // their names.
    int size() const;
    string toString() const;
    Symbol* getSymbol(int i) const;
    void clear();

    // Overloaded operators and their purpose:
    // 1) []    accessing i'th symbol in the vector. Returns pointer to
    //          Symbol class, to avoid inefficient copying.
    // 2) ()    accessing value of i'th symbol in the vector. It might be
    //          useful e.g. when simple checking is needed instead of
    //          operations on Symbol object.
    // 3) +     appends symbol at the end of the vector. It is more compact
    //          than explicitly calling appendSymbol(). Two versions:
    //          with int and Symbol*, provides flexibility.
    // 4) ==    Compares entries of two words vectors and if the are the
    //          same returns true, otherwise false is returned.
    Symbol* operator[](int i);
    int operator()(int i);
    void operator+(const int& a);
    void operator+(Symbol* a);
    bool operator == (const Word &b) const;

private:
    vector<Symbol*> _entries;
};


#endif //BACHELOR_THESIS_FEATURE_VECTOR_H
