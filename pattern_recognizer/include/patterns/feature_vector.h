//
// Created by dybisz on 17.12.15.
//

#ifndef BACHELOR_THESIS_FEATURE_VECTOR_H
#define BACHELOR_THESIS_FEATURE_VECTOR_H

#include <vector>
#include <string>
#include "symbol.h"

using namespace std;
// TODO overload << operator to append symbol
// TODO try to overload >> to get rid of last symbol

class FeatureVector{
public:
    ~FeatureVector() {
        for (auto it = _entries.begin() ; it != _entries.end(); ++it)
        {
            delete (*it);
        }
        _entries.clear();
    }
    void appendSymbol(int symbol) {
        Symbol* a = new Symbol(symbol);
        _entries.push_back(a);
    }

    FeatureVector operator+(int symbol) const{
        FeatureVector temp;
        temp.appendSymbol(symbol);
        return temp;
    }

    string toString() {
        string out = "";
        for (auto it = _entries.begin() ; it != _entries.end(); ++it)
        {
            out += ((*it)->getVal());
        }
    }

private:
    vector<Symbol*> _entries;
};


#endif //BACHELOR_THESIS_FEATURE_VECTOR_H
