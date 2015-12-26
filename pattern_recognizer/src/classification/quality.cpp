//
// Created by dybisz on 23.12.15.
//

#include "quality.h"

/* ----------------------- */
/* -----MAIN METHODS ----- */
/* ----------------------- */

vector<Word *> *quality::gatherTPDistinct(vector<Language *> *nativeLanguages,
                                          vector<Language *> *foreignLanguages,
                                          DFA *dfa) {
    vector<Word *> *TP = new vector<Word *>();

    // Gather TP from native languages
    for (auto lang = nativeLanguages->begin();
         lang != nativeLanguages->end(); ++lang) {
        _getTPFrom((*lang), dfa, (*lang)->getStates(), TP);
    }

    // Gather TP from foreign languages
    for (auto lang = foreignLanguages->begin();
         lang != foreignLanguages->end(); ++lang) {
        _getTPFrom((*lang), dfa, (*lang)->getStates(), TP);
    }

    return TP;
}


vector<Word *> *quality::gatherTPOverall(vector<Language *> *nativeLanguages,
                                         vector<Language *> *foreignLanguages,
                                         DFA *dfa) {
    vector<Word *> *TP = new vector<Word *>();

    // Gather TP from native languages
    for (auto lang = nativeLanguages->begin();
         lang != nativeLanguages->end(); ++lang) {
        _getTPFrom((*lang), dfa, (*lang)->getStates(), TP);
    }

    // Gather all states corresponding to foreign languages to prevent
    // treating them as a distinct ones.
    vector<State *> foreignStates = _collectStates(foreignLanguages);

    // Gather TP from foreign languages
    for (auto lang = foreignLanguages->begin();
         lang != foreignLanguages->end(); ++lang) {
        _getTPFrom((*lang), dfa, &foreignStates, TP);
    }

    return TP;
}

vector<Word *> *quality::gatherFNDistinct(vector<Language *> *nativeLanguages,
                                          vector<Language *> *foreignLanguages,
                                          DFA *dfa) {
    vector<Word *> *FN = new vector<Word *>();

    // Gather FN from native languages
    for (auto lang = nativeLanguages->begin();
         lang != nativeLanguages->end(); ++lang) {
        _getFNFrom((*lang), dfa, (*lang)->getStates(), FN);
    }

    // Gather FN from foreign languages
    for (auto lang = foreignLanguages->begin();
         lang != foreignLanguages->end(); ++lang) {
        _getFNFrom((*lang), dfa, (*lang)->getStates(), FN);
    }
    return FN;
}

vector<Word *> *quality::gatherFNOverall(vector<Language *> *nativeLanguages,
                                         vector<Language *> *foreignLanguages,
                                         DFA *dfa) {
    vector<Word *> *FN = new vector<Word *>();

    // Gather FN from native languages
    for (auto lang = nativeLanguages->begin();
         lang != nativeLanguages->end(); ++lang) {
        _getFNFrom((*lang), dfa, (*lang)->getStates(), FN);
    }

    // Gather all states corresponding to foreign languages to prevent
    // treating them as a distinct ones.
    vector<State *> foreignStates = _collectStates(foreignLanguages);

    // Gather FN from foreign langauges
    for (auto lang = foreignLanguages->begin();
         lang != foreignLanguages->end(); ++lang) {
        _getFNFrom((*lang), dfa, &foreignStates, FN);
    }

    return FN;
}

double quality::computeTPDistinct(vector<Language *> *nativeLanguages,
                                  vector<Language *> *foreignLanguages,
                                  DFA *dfa) {
    double TPWords = _numberOfTPDistinct(nativeLanguages, foreignLanguages,
                                         dfa);
    int numberOfWords = _countNumberOfWords(nativeLanguages) +
                        _countNumberOfWords(foreignLanguages);
    double tpPercentage = (TPWords) / numberOfWords;
    return tpPercentage;
}

double quality::computeTPOverall(vector<Language *> *nativeLanguages,
                                 vector<Language *> *foreignLanguages,
                                 DFA *dfa) {
    double TPWords = _numberOfTPOverall(nativeLanguages, foreignLanguages,
                                        dfa);
    int numberOfWords = _countNumberOfWords(nativeLanguages) +
                        _countNumberOfWords(foreignLanguages);
    double tpPercentage = (TPWords) / numberOfWords;
    return tpPercentage;
}

double quality::computeFNDistinct(vector<Language *> *nativeLanguages,
                                  vector<Language *> *foreignLanguages,
                                  DFA *dfa) {
    double FNWords = _numberOfFNDistinct(nativeLanguages, foreignLanguages,
                                         dfa);
    int numberOfWords = _countNumberOfWords(nativeLanguages) +
                        _countNumberOfWords(foreignLanguages);
    double fnPercentage = (FNWords) / numberOfWords;
    return fnPercentage;
}

double quality::computeFNOverall(vector<Language *> *nativeLanguages,
                                 vector<Language *> *foreignLanguages,
                                 DFA *dfa) {
    double FNWords = _numberOfFNOverall(nativeLanguages, foreignLanguages,
                                        dfa);
    int numberOfWords = _countNumberOfWords(nativeLanguages) +
                        _countNumberOfWords(foreignLanguages);
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

int quality::_numberOfTPDistinct(vector<Language *> *nativeLanguages,
                                 vector<Language *> *foreignLanguages,
                                 DFA *dfa) {
    vector<Word *> *TP = quality::gatherTPDistinct(nativeLanguages,
                                                   foreignLanguages,
                                                   dfa);
    int TPwords = TP->size();
    delete TP;
    return TPwords;
}

int quality::_numberOfTPOverall(vector<Language *> *nativeLanguages,
                                vector<Language *> *foreignLanguages,
                                DFA *dfa) {
    vector<Word *> *TP = quality::gatherTPOverall(nativeLanguages,
                                                  foreignLanguages,
                                                  dfa);
    int TPwords = TP->size();
    delete TP;
    return TPwords;
}

int quality::_numberOfFNDistinct(vector<Language *> *nativeLanguages,
                                 vector<Language *> *foreignLanguages,
                                 DFA *dfa) {
    vector<Word *> *FN = quality::gatherFNDistinct(nativeLanguages,
                                                   foreignLanguages,
                                                   dfa);
    int FNwords = FN->size();
    delete FN;
    return FNwords;
}

int quality::_numberOfFNOverall(vector<Language *> *nativeLanguages,
                                vector<Language *> *foreignLanguages,
                                DFA *dfa) {
    vector<Word *> *FN = quality::gatherFNOverall(nativeLanguages,
                                                  foreignLanguages,
                                                  dfa);
    int FNwords = FN->size();
    delete FN;
    return FNwords;
}

void quality::_getTPFrom(Language *pLanguage, DFA *pDFA,
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

void quality::_getFNFrom(Language *pLanguage, DFA *pDFA,
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


