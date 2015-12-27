//
// Created by dybisz on 19.12.15.
//

#include <features_vector.h>
#include <stdexcept>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

FeaturesVector::FeaturesVector() {}

FeaturesVector::FeaturesVector(const vector<double> &entries){
    for(auto it = entries.begin(); it != entries.end(); ++it) {
        _entries.push_back((*it));
    }
}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

void FeaturesVector::appendSymbol(double symbol){
    _entries.push_back(symbol);
}

void FeaturesVector::setEntry(int i, double val) {
    _entries[i] = val;
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

int FeaturesVector::size() const {
    return _entries.size();
}

string FeaturesVector::toString() const {
    string out = "";
    for (auto it = _entries.begin() ; it != _entries.end(); ++it)
    {
        out += to_string(*it);
    }
    return out;
}

double FeaturesVector::getEntry(int i) const {
    return _entries[i];
}

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */

double FeaturesVector::operator[](int i) {
    if (size() < 1) {
        throw invalid_argument("size of word is < 1");
    }

    return this->getEntry(i);
}

void FeaturesVector::operator+(const double& a) {
    this->appendSymbol(a);
}

bool FeaturesVector::operator == (const FeaturesVector &b) const {
    if(this->size() != b.size()) {
        throw invalid_argument( "Feature vectors sizes do not match.");
    }

    bool areTheSame = true;

    for(int i = 0; i < this->size(); i++) {
        if(_entries[i] != b.getEntry(i)){
            areTheSame = false;
            break;
        }
    }

    return areTheSame;
}

