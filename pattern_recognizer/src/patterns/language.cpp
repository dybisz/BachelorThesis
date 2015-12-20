//
// Created by dybisz on 20.12.15.
//

#include <logger.h>
#include "language.h"

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

Language::Language(Pattern *pPattern, Alphabet pAlphabet,
                   vector<State *> pStates) : _alphabet(pAlphabet),
                                              _states(pStates) {
    try {
        _produceWordsFromPattern(pPattern);
    }
    catch (exception &e) {
        LOG_ERROR(e.what());
    }
}

Language::~Language() {
    // Release words
    for (auto iter = _words.begin(); iter != _words.end(); ++iter) {
        delete (*iter);
    }
    // Release states
    for (auto iter = _states.begin(); iter != _states.end(); ++iter) {
        delete (*iter);
    }
}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

void Language::_produceWordsFromPattern(Pattern *pPattern) {
    // Get features
    vector<FeaturesVector *> *features = pPattern->getFeatures();
    // TODO create method for getting number of features
    int numberOfFeatures = pPattern->getVector(0)->size();

    // Convert each features vector to word
    for (auto iter = features->begin(); iter != features->end(); ++iter) {
        vector<Symbol> symbols;

        for (int i = 0; i < numberOfFeatures; i++) {
            double entry = (*(*iter))[i];
            // Stretch normalized entry to the alphabet size
            entry *= _alphabet.size();
            Symbol symbol = _alphabet.convertToSymbol(entry);
            symbols.push_back(symbol);

        }
        // Create word and save it.
        Word *word = new Word(symbols);
        _words.push_back(word);
    }

}

string Language::toString() {
    string out = "<< LANGUAGE SUMMARY >>\n";
    out += statesToString();
    out += "\n";
    out += alphabetToString();
    out += "\n";
    out += wordsToString();
    out += "\n";
    return out;
}

string Language::statesToString() {
    string out = "[States]: \n";
    for (auto iter = _states.begin(); iter != _states.end(); ++iter) {
        out += (*iter)->toString();
        out += "\n";
    }
    return out;
}

string Language::wordsToString() {
    string out = "[Words]: \n";
    for (auto iter = _words.begin(); iter != _words.end(); ++iter) {
        out += (*iter)->toString();
        out += "\n";
    }

    return out;
}

string Language::alphabetToString() {
    string out = "[Alphabet]: \n";
    out += _alphabet.toString();
    out += "\n";
    return out;
}

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */


