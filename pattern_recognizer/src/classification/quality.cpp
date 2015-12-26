//
// Created by dybisz on 23.12.15.
//

#include "quality.h"

/* ----------------------- */
/* -----MAIN METHODS ----- */
/* ----------------------- */

int quality::numberOfTrueDistinct(vector<Language *> *pLanguages,
                                  DFA *dfa) {
    vector<Word *> *TP = quality::_gatherTrueDistinct(pLanguages,
                                                      dfa);
    int TPwords = TP->size();
    delete TP;
    return TPwords;
}

int quality::numberOfTrueOverall(vector<Language *> *pLanguages,
                                 DFA *dfa) {
    vector<Word *> *TP = quality::_gatherTrueOverall(pLanguages,
                                                     dfa);
    int TPwords = TP->size();
    delete TP;
    return TPwords;
}

int quality::numberOfFalseDistinct(vector<Language *> *pLanguages,
                                   DFA *dfa) {
    vector<Word *> *FN = quality::_gatherFalseDistinct(pLanguages,
                                                       dfa);
    int FNwords = FN->size();
    delete FN;
    return FNwords;
}

int quality::numberOfFalseOverall(vector<Language *> *pLanguages,
                                  DFA *dfa) {
    vector<Word *> *FN = quality::_gatherFalseOverall(pLanguages,
                                                      dfa);
    int FNwords = FN->size();
    delete FN;
    return FNwords;
}


double quality::percentageTrueDistinct(vector<Language *> *pLanguages,
                                       DFA *dfa) {
    double TPWords = numberOfTrueDistinct(pLanguages,
                                          dfa);
    int numberOfWords = _countNumberOfWords(pLanguages);
    double tpPercentage = (TPWords) / numberOfWords;
    return tpPercentage;
}

double quality::percentageTrueOverall(vector<Language *> *pLanguages,
                                      DFA *dfa) {
    double TPWords = numberOfTrueOverall(pLanguages,
                                         dfa);
    int numberOfWords = _countNumberOfWords(pLanguages);
    double tpPercentage = (TPWords) / numberOfWords;
    return tpPercentage;
}

double quality::percentageFalseDistinct(vector<Language *> *pLanguages,
                                        DFA *dfa) {
    double FNWords = numberOfFalseDistinct(pLanguages,
                                           dfa);
    int numberOfWords = _countNumberOfWords(pLanguages);
    double fnPercentage = (FNWords) / numberOfWords;
    return fnPercentage;
}

double quality::percentageFalseOverall(vector<Language *> *pLanguages,
                                       DFA *dfa) {
    double FNWords = numberOfFalseOverall(pLanguages,
                                          dfa);
    int numberOfWords = _countNumberOfWords(pLanguages);
    double fnPercentage = (FNWords) / numberOfWords;
    return fnPercentage;
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */

void quality::_convertWords(vector<Language *> *pLanguages) {
    for (auto lang = pLanguages->begin(); lang != pLanguages->end(); ++lang) {
        vector<Word *> words = *(*lang)->getWords();
        for (auto word = words.begin(); word != words.end(); ++word) {

            // Decrease all entries by 1
            _convertWord((*word));
        }
    }
}

void quality::_convertWord(Word *word) {
    // Save previous word
    Word temp = new Word(*word);
    // Clear current one
    word->clear();

    for (int i = 0; i < temp.size(); ++i) {
        int val = temp.getSymbol(i)->getVal();
        --val;
        Symbol *symbol = new Symbol(val);
        word->appendSymbol(symbol);
    }
}

bool quality::_stateOnList(int state, vector<State *> *pStates) {
    for (int i = 0; i < pStates->size(); ++i) {
        if (state == (*pStates)[i]->getVal()) {
            return true;
        }
    }

    return false;
}

int quality::_countNumberOfWords(vector<Language *> *languages) {
    int size = 0;
    for (auto lang = languages->begin(); lang != languages->end(); ++lang) {
        size += (*lang)->size();
    }
    return size;
}

vector<State *> quality::_collectStates(vector<Language *> *pLanguages) {
    vector<State *> states;

    for (auto lang = pLanguages->begin(); lang != pLanguages->end(); ++lang) {

        vector<State *> localStates = *((*lang)->getStates());
        for (int i = 0; i < localStates.size(); i++) {
            states.push_back(localStates[i]);
        }

    }
    return states;
}

vector<Word *> *quality::_gatherTrueDistinct(
        vector<Language *> *pLanguages,
        DFA *dfa) {
    vector<Word *> *TP = new vector<Word *>();

    // Gather TP from native languages
    for (auto lang = pLanguages->begin();
         lang != pLanguages->end(); ++lang) {
        _getTrueOnesFrom((*lang), dfa, (*lang)->getStates(), TP);
    }

    return TP;
}


vector<Word *> *quality::_gatherTrueOverall(vector<Language *> *pLanguages,
                                            DFA *dfa) {
    vector<Word *> *TP = new vector<Word *>();

    // Gather all states corresponding to native languages to prevent
    // treating them as a distinct ones.
    vector<State *> nativeStates = _collectStates(pLanguages);

    // Gather TP from native languages
    for (auto lang = pLanguages->begin();
         lang != pLanguages->end(); ++lang) {
        _getTrueOnesFrom((*lang), dfa, &nativeStates, TP);
    }

    return TP;
}

vector<Word *> *quality::_gatherFalseDistinct(
        vector<Language *> *pLanguages,
        DFA *dfa) {
    vector<Word *> *FN = new vector<Word *>();

    // Gather FN from foreign languages
    for (auto lang = pLanguages->begin();
         lang != pLanguages->end(); ++lang) {
        _getFalseOnesFrom((*lang), dfa, (*lang)->getStates(), FN);
    }
    return FN;
}

vector<Word *> *quality::_gatherFalseOverall(
        vector<Language *> *pLanguages,
        DFA *dfa) {
    vector<Word *> *FN = new vector<Word *>();

    // Gather all states corresponding to native languages to prevent
    // treating them as a distinct ones.
    vector<State *> nativeStates = _collectStates(pLanguages);

    // Gather FN from foreign langauges
    for (auto lang = pLanguages->begin();
         lang != pLanguages->end(); ++lang) {
        _getFalseOnesFrom((*lang), dfa, &nativeStates, FN);
    }

    return FN;
}

void quality::_getTrueOnesFrom(Language *pLanguage, DFA *pDFA,
                               vector<State *> *pCorrectStates,
                               vector<Word *> *pStorage) {

    vector<Word *> *words = pLanguage->getWords();

    for (auto word = words->begin(); word != words->end(); ++word) {

        // Check ending state
        int endState = pDFA->compute(*(*word));

        // Check correctness of computations
        if (_stateOnList(endState, pCorrectStates))
            pStorage->push_back((*word));
    }
}

void quality::_getFalseOnesFrom(Language *pLanguage, DFA *pDFA,
                                vector<State *> *pCorrectStates,
                                vector<Word *> *pStorage) {

    vector<Word *> *words = pLanguage->getWords();

    for (auto word = words->begin(); word != words->end(); ++word) {

        // Check ending state
        int endState = pDFA->compute(*(*word));

        // Check correctness of computations
        if (!_stateOnList(endState, pCorrectStates))
            pStorage->push_back((*word));
    }
}


