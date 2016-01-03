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
    Language(Alphabet alphabet);
    Language(Pattern* pPattern, Alphabet pAlphabet, vector<State *> pStates);
    Language(Pattern* pPattern, Alphabet pAlphabet);
    Language(vector<Word*> &words, Alphabet pAlphabet, vector<State *> pStates);
    Language(vector<Word*> &words, Alphabet pAlphabet);
    Language(vector<Word*> words, Language* lang);

    ~Language();

    string toString();
    string statesToString();
    string wordsToString();
    string alphabetToString();

    // Different words accesing:
    // 1) returns ith pointer to the word, not interfering with set of words.
    // 2) removes and restarturns last element from the set of words.
    Word* getWord(int i);
    Word* stealLastWord();

    const vector<State*>* getStates() const;
    vector<Word*>* getWords();
    Alphabet getAlphabet() const;
    int size() const;

    // Checks if state corresponds to this language
    bool isCorrespondingState(State*) const;
    void setStates(std::vector<State*> states);

    void addWord(Word* word);

private:
    Alphabet _alphabet;
    vector<Word*> _words;
    vector<State*> _states;

    void _produceWordsFromPattern(Pattern *pPattern);
};

#endif //BACHELOR_THESIS_LANGUAGE_H
