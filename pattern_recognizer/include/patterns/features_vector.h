//
// Created by dybisz on 19.12.15.
//

#ifndef BACHELOR_THESIS_FEATURES_VECTOR_H
#define BACHELOR_THESIS_FEATURES_VECTOR_H

#include <vector>
#include <string>
using namespace std;

class FeaturesVector {
public:
    FeaturesVector();
    FeaturesVector(const vector<double> &entries);

    void appendSymbol(double symbol);

    int size() const;
    string toString() const;
    double getEntry(int i) const;

    double operator[](int i);
    void operator+(const double& a);
    bool operator == (const FeaturesVector &b) const;
private:
    vector<double> _entries;
};

#endif //BACHELOR_THESIS_FEATURES_VECTOR_H
