//
// Created by dybisz on 20.12.15.
//

#include <logger.h>
#include "language.h"

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

Language::Language(Alphabet alphabet): _alphabet(alphabet){

}

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

Language::Language(Pattern *pPattern, Alphabet pAlphabet)
                        : _alphabet(pAlphabet) {
    try {
        _produceWordsFromPattern(pPattern);
    }
    catch (exception &e) {
        LOG_ERROR(e.what());
    }
}

Language::Language(vector<Word *> &words, Alphabet pAlphabet,
                   vector<State *> pStates) : _words(words),
                                              _alphabet(pAlphabet),
                                              _states(pStates) {
}

Language::Language(vector<Word *> &words, Alphabet pAlphabet)
                                                : _words(words),
                                              _alphabet(pAlphabet){
}

Language::Language(vector<Word *> words, Language *lang) :
        _alphabet(lang->getAlphabet()) {

    // Create new pointers to words
    for (auto w = words.begin(); w != words.end(); ++w) {
        Word* word = new Word((*w));
        _words.push_back(word);
    }

    // Copy states values
    const vector<State *> *lStates = lang->getStates();

    for (auto pState = lStates->begin(); pState != lStates->end(); ++pState) {
        State *s = new State(**pState);
        _states.push_back(s);
    }
}

Language::~Language() {
/*
    // Release words
    for (auto iter = _words.begin(); iter != _words.end(); ++iter) {
        delete (*iter);
    }
    // Release states
    for (auto iter = _states.begin(); iter != _states.end(); ++iter) {
        delete (*iter);
    }*/

    for(unsigned int i = 0; i < _words.size(); i++){
        delete (_words)[i];
    }

    for(unsigned int i = 0; i < _states.size(); i++){
        delete (_states)[i];
    }

}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

const vector<State*>* Language::getStates() const{
    return &_states;
}

vector<Word *> *Language::getWords() {
    return &_words;
}

Alphabet Language::getAlphabet() const {
    return _alphabet;
}

int Language::size() const {
    return _words.size();
}

void Language::setStates(std::vector<State *> states) {
    this->_states = states;
}

bool Language::isCorrespondingState(State *state) const{
    for (unsigned int i = 0; i < _states.size(); i++) {
        if ((*_states[i]) == *state)
            return true;
    }
    return false;
}

void Language::addWord(Word* word){
    this->_words.push_back(word);
}

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
            entry *= (double) _alphabet.size();

//            if(entry > _alphabet.size()) cout << "before: " << (*(*iter))[i] << "entry: " << entry << " alphabet.sz(): " << _alphabet.size() << endl;

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
// string out = "[States]: \n";
    string out = "";
    for (auto iter = _states.begin(); iter != _states.end(); ++iter) {
        out += (*iter)->toString();
        out += " ";
    }
// out += "\n";
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

Word *Language::getWord(int i) {
    return _words[i];
}

Word *Language::stealLastWord() {
    Word *word = _words.back();
    _words.pop_back();
    return word;
}

/* --------------------- */
/* ----- OPERATORS ----- */
/* --------------------- */


