//
// Created by dybisz on 19.12.15.
//

#ifndef BACHELOR_THESIS_LANGUAGE_H
#define BACHELOR_THESIS_LANGUAGE_H

#include <language/word.h>
#include <language/alphabet.h>

#include <automata/state.h>

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

    /*
     * Removes all duplicate words.
     * The resulting language is then a proper set of words.
     */
    void removeDuplicates();

    /*
     * Returns number of occurrences of input word
     */
    int numberOfOccurrences(const Word& word);

private:
    Alphabet _alphabet;
    vector<Word*> _words;
    vector<State*> _states;

    void _safeDeleteContent(vector<State *> vector);

    /*
     * Returns a vector of words without any duplications.
     * Allocates memory for each appended word.
     */
    vector<Word*> getWordsWithoutDuplicates(const vector<Word*>& words);

    /*
     * New Words are set. The current ones are freed
     * and the vector is cleared.
     *
     * Reallocates memory for the new words. Does not touch the words
     * in input vector.
     */
    void setNewWords(const vector<Word*>& words);

    /*
     * Frees all the memory taken by words
     */
    void freeWordsMemory();

    /*
     * Frees all the memory taken by states
     */
    void freeStatesMemory();
};

#endif //BACHELOR_THESIS_LANGUAGE_H
