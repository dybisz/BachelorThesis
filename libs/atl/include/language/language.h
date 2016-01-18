//
// Created by dybisz on 19.12.15.
//

#ifndef BACHELOR_THESIS_LANGUAGE_H
#define BACHELOR_THESIS_LANGUAGE_H

#include <language/word.h>
#include <language/alphabet.h>

#include <automata/state.h>

#include <patterns/pattern.h>

#include <vector>

using namespace std;
/**
 * Ownership:
 *      Words
 */
class Language {
public:
    Language(Alphabet alphabet);
    Language(const Language& language);
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
    Word* getWord(int i) const;
    Word* stealLastWord();

    vector<State*>* getStates();
    vector<Word*>* getWords();
    Alphabet getAlphabet() const;
    void setStates(std::vector<State*> states);
    int size() const;

    // Checks if state corresponds to this language
    bool isCorrespondingState(State*) const;

    void addWord(Word* word);

    /*
     * Appends all words from given language.
     * Memory for all words is reallocated.
     */
    void append(const Language& language);

private:
    Alphabet _alphabet;
    vector<Word*> _words;
    vector<State*> _states;

    void _produceWordsFromPattern(Pattern *pPattern);

    void _safeDeleteContent(vector<State *> vector);
};

#endif //BACHELOR_THESIS_LANGUAGE_H
