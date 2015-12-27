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
    Language(vector<Word*> &words, Alphabet pAlphabet, vector<State *> pStates);
    Language(vector<Word*> words, Language* lang);
    ~Language();

    string toString();
    string statesToString();
    string wordsToString();
    string alphabetToString();

    // Different words accesing:
    // 1) returns ith pointer to the word, not interfering with set of words.
    // 2) removes and returns last element from the set of words.
    Word* getWord(int i);
    Word* stealLastWord();

    vector<State*>* getStates();
    vector<Word*>* getWords();
    Alphabet getAlphabet();
    void setStates(std::vector<State*> states);

    // Returns number of words
    int size() const;

    // Checks if state corresponds to this language
    bool isCorrespondingState(State*);

private:
    Alphabet _alphabet;
    vector<Word*> _words;
    vector<State*> _states;

    void _produceWordsFromPattern(Pattern *pPattern);
};

#endif //BACHELOR_THESIS_LANGUAGE_H
