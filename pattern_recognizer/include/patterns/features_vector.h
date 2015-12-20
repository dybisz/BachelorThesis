//
// Created by dybisz on 19.12.15.
//

#ifndef BACHELOR_THESIS_FEATURES_VECTOR_H
#define BACHELOR_THESIS_FEATURES_VECTOR_H

#include <vector>
#include <string>

using namespace std;

/*
 * There are only two reason for this class: manipulating features stored in
 * the vector in a transparent way and keeping level of abstraction.
 */
class FeaturesVector {
public:
    // Feature vector can be created:
    // 1) Empty.
    // 2) From provided vectors of doubles - WARNING: copy will be created.
    FeaturesVector();
    FeaturesVector(const vector<double> &entries);

    // Instead of using operators, one can explicitly call one of the
    // following methods to append symbols.
    void appendSymbol(double symbol);
    void setEntry(int i, double val);

    // Auxiliary methods, which definition is selfexplanatory regarding
    // their names.
    int size() const;
    string toString() const;
    double getEntry(int i) const;

    // Overloaded operators and their purpose:
    // 1) []    accessing i'th value in the vector and returns its value.
    // 2) +     appends symbol at the end of the vector. It is more compact
    //          than explicitly calling appendSymbol().
    // 3) ==    Compares entries of two feature vectors and if they are the
    //          same returns true, otherwise false is returned.
    double operator[](int i);
    void operator+(const double& a);
    bool operator == (const FeaturesVector &b) const;

private:
    vector<double> _entries;
};

#endif //BACHELOR_THESIS_FEATURES_VECTOR_H
