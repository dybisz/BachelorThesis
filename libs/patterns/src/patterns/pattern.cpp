//
// Created by dybisz on 19.12.15.
//

#include <patterns/pattern.h>
#include <stdexcept>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

Pattern::Pattern(int label) : _label(label) {

}

Pattern::Pattern(vector<FeaturesVector *> *features, int label) : _label(
        label) {
    this->_features = (*features);
}

Pattern::~Pattern() {
    for (auto iter = _features.begin(); iter != _features.end(); ++iter) {
        delete (*iter);
    }
}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

void Pattern::appendFeatureVector(FeaturesVector *featuresVector) {
    if (_features.size() != 0 &&
        _features[0]->size() != featuresVector->size()) {
        throw invalid_argument("Feature vectors sizes do not match.");
    }

    this->_features.push_back(featuresVector);
}

FeaturesVector *Pattern::getVector(unsigned int i) {
    if (_features.size() <= i) {
        throw invalid_argument("Index out of bound");
    }
    return _features[i];
}

double Pattern::getFeatureMin(int i) {
    double min = INT32_MAX;
    for (auto iter = _features.begin(); iter != _features.end(); ++iter) {
        double value = (*(*iter))[i]; // TODO check if correct
        if (value < min) min = value;
    }
    return min;
}

double Pattern::getFeatureMax(int i) {
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

int Pattern::size() {
    return this->_features.size();
}

int Pattern::getLabel() {
    return this->_label;
}

vector<FeaturesVector *> *Pattern::getFeatures() {
    return &_features;
};

string Pattern::toString() {
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

FeaturesVector *Pattern::operator[](int i) {
    return this->getVector(i);
}