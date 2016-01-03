//
// Created by dybisz on 19.12.15.
//

#ifndef BACHELOR_THESIS_PATTERN_H
#define BACHELOR_THESIS_PATTERN_H

#include <features_vector.h>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
/*
 * Class represents a patter via set of features vectors and a label;
 */
class Pattern {
public:
    Pattern(int label);
    Pattern(vector<FeaturesVector*>* features, int label);
    ~Pattern();

    void appendFeatureVector(FeaturesVector* featuresVector);
    FeaturesVector* getVector(unsigned int i);
    double getFeatureMin(int i);
    double getFeatureMax(int i);

    int size();
    int getLabel();
    vector<FeaturesVector*>* getFeatures();
    string toString();

    FeaturesVector* operator[](int i);
private:
    vector<FeaturesVector*> _features;
    int _label;
};

#endif //BACHELOR_THESIS_PATTERN_H
