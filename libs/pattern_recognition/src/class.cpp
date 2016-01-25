//
// Created by dybisz on 19.12.15.
//

#include "class.h"
#include <stdexcept>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

Class::Class(int label) : _label(label) {

}

Class::Class(vector<FeaturesVector *> *features, int label) : _label(
        label) {
    this->_features = (*features);
}

Class::~Class() {
    for (auto iter = _features.begin(); iter != _features.end(); ++iter) {
        delete (*iter);
    }
}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

void Class::appendFeatureVector(FeaturesVector *featuresVector) {
    if (_features.size() != 0 &&
        _features[0]->size() != featuresVector->size()) {
        throw invalid_argument("Feature vectors sizes do not match.");
    }

    this->_features.push_back(featuresVector);
}

FeaturesVector *Class::getVector(unsigned int i) {
    if (_features.size() <= i) {
        throw invalid_argument("Index out of bound");
    }
    return _features[i];
}

double Class::getFeatureMin(int i) {
    double min = INT32_MAX;
    for (auto iter = _features.begin(); iter != _features.end(); ++iter) {
        double value = (*(*iter))[i]; // TODO check if correct
        if (value < min) min = value;
    }
    return min;
}

double Class::getFeatureMax(int i) {
    double max = INT32_MIN;
    for (auto iter = _features.begin(); iter != _features.end(); ++iter) {
        double value = (*(*iter))[i]; // TODO check if correct
        if (value > max) max = value;
    }
    return max;
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

FeaturesVector *Class::popBack() {
    int lastIndex = _features.size() - 1;
    FeaturesVector* fv = _features[lastIndex];
    _features.pop_back();

    return fv;
}

int Class::size() const {
    return this->_features.size();
}

int Class::getLabel() const{
    return this->_label;
}

vector<FeaturesVector *> *Class::getFeatures() {
    return &_features;
};

string Class::toString() {
    string out = "[";
    out += to_string(_label);
    out += "]\n";

    for (auto it = _features.begin(); it != _features.end(); ++it) {
        out += (*it)->toString();
        out += "\n";
    }
    return out;
}

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */

FeaturesVector *Class::operator[](int i) {
    return this->getVector(i);
}
