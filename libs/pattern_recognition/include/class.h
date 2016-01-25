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
class Class {
public:
    Class(int label);
    Class(vector<FeaturesVector*>* features, int label);
    ~Class();

    void appendFeatureVector(FeaturesVector* featuresVector);
    FeaturesVector* getVector(unsigned int i);
    double getFeatureMin(int i);
    double getFeatureMax(int i);

    /*
     * Deletes and pops back the last feature vector
     */
    FeaturesVector* popBack();

    int size() const;
    int getLabel() const;
    vector<FeaturesVector*>* getFeatures();
    string toString();

    FeaturesVector* operator[](int i);
private:
    vector<FeaturesVector*> _features;
    int _label;
};

#endif //BACHELOR_THESIS_PATTERN_H