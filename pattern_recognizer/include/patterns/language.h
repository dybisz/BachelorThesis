//
// Created by dybisz on 19.12.15.
//

#ifndef BACHELOR_THESIS_LANGUAGE_H
#define BACHELOR_THESIS_LANGUAGE_H

#include <vector>
#include "pattern.h"
#include "word.h"
#include "state.h"
#include "alphabet.h"

using namespace std;

class Language {
public:

    Language(Pattern * pPattern, Alphabet pAlphabet, vector<State *> pStates);
    ~Language();

    string toString();
    string statesToString();
    string wordsToString();
    string alphabetToString();
    
private:
    Alphabet _alphabet;
    vector<Word*> _words;
    vector<State*> _states;

    void _produceWordsFromPattern(Pattern *pPattern);
};

#endif //BACHELOR_THESIS_LANGUAGE_H
