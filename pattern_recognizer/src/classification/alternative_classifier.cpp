//
// Created by dybisz on 30.12.15.
//

#include <logger.h>
#include <utils.h>
#include <sets_ disassociation.h>
#include <logger/log.h>
#include <quality.h>
#include <clock.h>
#include "alternative_classifier.h"

int AlternativeClassifier::FOREIGN_LABEL = -1;

AlternativeClassifier::AlternativeClassifier(vector<Language *> *nativePatterns,
                                             vector<Language *> *foreignPatterns,
                                             unsigned int states,
                                             unsigned int alphabetSize,
                                             double testingSetRatio) {
    _nativeTrainingSet = nativePatterns;
    _foreignTrainingSet = foreignPatterns;
    _statesNum = states;
    _alphabetSize = alphabetSize;
    _wordsNum = _calculateWordsNum(nativePatterns, foreignPatterns);

    /* ----- TESTING SET ----- */
    this->_nativeTestingSet = set_disassociation::detachWords(testingSetRatio,
                                                              _nativeTrainingSet);
    this->_foreignTestingSet = set_disassociation::detachWords(testingSetRatio,
                                                               _foreignTrainingSet);
    /* ----------------------- */

    try {
        _allocateLabeledWordsMap(nativePatterns, foreignPatterns,
                                 _trainingWordsNum,
                                 _labelNum);
        _allocateTransitionTable(_statesNum, _alphabetSize);
        _allocateSmartStateTable(_statesNum, _labelNum);
        _allocateOutputArray(_statesNum);
    }
    catch (exception &e) {
        LOG_ERROR(e.what());
    }
}

AlternativeClassifier::~AlternativeClassifier() {
    // Pointers to native words
    for (auto it = _nativeTrainingSet->begin();
         it != _nativeTrainingSet->end(); ++it) {
        delete *it;
    }
    delete _nativeTrainingSet;

    // Pointers to foreign words
    for (auto it = _foreignTrainingSet->begin();
         it != _foreignTrainingSet->end(); ++it) {
        delete *it;
    }
    delete _foreignTrainingSet;

    // Pointers to native words
    for (auto it = _nativeTestingSet->begin();
         it != _nativeTestingSet->end(); ++it) {
        delete *it;
    }
    delete _nativeTestingSet;

    // Pointers to foreign words
    for (auto it = _foreignTestingSet->begin();
         it != _foreignTestingSet->end(); ++it) {
        delete *it;
    }
    delete _foreignTestingSet;

    // Smart States
    for (int i = 0; i < _statesNum; ++i) {
        delete[] _h[i];
    }

    delete[] _h;
    delete[] _o;
}

void AlternativeClassifier::compute() {
    _randomizeTransitionTable();
    _computeSmartStates();
    _determineOutput(_o);
    _currentFitness = _fitness();


    logger::log(Verbose(HILL_CLIMBER), "Computations Starts... ");
    for (int iter = 1; iter <= global_settings::MAX_ITER; iter++) {
        clk::startClock();
        _ttOrigin = _randomTransitionChange();

        _computeSmartStates();
        int output[_statesNum];
        _determineOutput(&output[0]);
        double alt_fitness = _fitness();

        if (alt_fitness >= _currentFitness) {
            _currentFitness = alt_fitness;
            _swapOutput(&output[0]);

        } else {
            _tt[_ttOrigin.index] = _ttOrigin.state;
        }

        if (_currentFitness == 1) break;

        _printInfoAndPlot(clk::stopClock(), iter);
    }
    logger::log(Verbose(HILL_CLIMBER), "Computations Ends");

    /* ----- Save To DFA ----- */
    TransitionFunction *tf = new TransitionFunction((unsigned int)_statesNum,
                                                    (unsigned int)_alphabetSize,
                                                    _tt);
    _dfa = new DFA(tf);

    /* ----- Update States In Languages ----- */
    _swapNativeStates(_nativeTrainingSet, _o);
    _swapNativeStates(_nativeTestingSet, _o);
    _swapForeignStates(_foreignTrainingSet, _o);
    _swapForeignStates(_foreignTestingSet, _o);

    /* ----- Quality Results ----- */
    _logDFA();
    _calculateAndPrintQualityResults(_dfa);
    delete _dfa;
}

void AlternativeClassifier::_allocateLabeledWordsMap(
        vector<Language *> *pNativePatterns,
        vector<Language *> *pForeignPatterns, int &wordsNum, int &labelNum) {

    labelNum = 0;
    wordsNum = 0;

    // Segregate natives
    for (auto it = pNativePatterns->begin();
         it != pNativePatterns->end(); ++it) {
        _assignWordsToLabel(labelNum, (*it)->getWords());
        wordsNum += (*it)->size();
        labelNum++;
    }

    // Segregate foreign
    FOREIGN_LABEL = labelNum;
    for (auto it = pForeignPatterns->begin();
         it != pForeignPatterns->end(); ++it) {
        _assignWordsToLabel(FOREIGN_LABEL, (*it)->getWords());
        wordsNum += (*it)->size();
    }
    labelNum++;
}

void AlternativeClassifier::_assignWordsToLabel(int label,
                                                vector<Word *> *pWords) {

    for (auto it = pWords->begin(); it != pWords->end(); ++it) {
        _wordsMap[label].push_back((*it));
    }

}

void AlternativeClassifier::_allocateTransitionTable(int nStates,
                                                     int nSymbols) {
    for (int i = 0; i < nStates * nSymbols; ++i) {
        _tt.push_back(-1);
    }
}

void AlternativeClassifier::_allocateSmartStateTable(int nStates,
                                                     int nLabels) {
    _h = new int *[nStates];

    for (int i = 0; i < nStates; ++i) {
        _h[i] = new int[nLabels];
    }
}

void AlternativeClassifier::_allocateOutputArray(int nStates) {
    _o = new int[nStates];
}

void AlternativeClassifier::_randomizeTransitionTable() {
    for (int state = 0; state < _statesNum; state++) {
        for (int symbol = 0; symbol < _alphabetSize; symbol++) {
            _setTT(state, symbol, utils::generateRandomNumber(0, _statesNum));
        }
    }
}

void AlternativeClassifier::_computeSmartStates() {
    _zero2DArray(_h, _statesNum, _labelNum);

    for (int label = 0; label < _labelNum; label++) {

        // Now we deal with set of words associated with each label
        int size = _wordsMap[label].size();
        for (int i_word = 0; i_word < size; i_word++) {
            Word *word = _wordsMap[label][i_word];
            _h[f(word)][label]++;
        }

    }
}

void AlternativeClassifier::_zero2DArray(int **array2D, int dim1, int dim2) {
    for (int x = 0; x < dim1; x++) {
        for (int y = 0; y < dim2; y++) {
            array2D[x][y] = 0;
        }
    }
}

// TODO words values still need to be decreased, which kinda sucks
int AlternativeClassifier::f(Word *pWord) {
    int currentState = 0;
    for (int i_symbol = 0; i_symbol < pWord->size(); i_symbol++) {
        int symbol = (*pWord)(i_symbol);
        currentState = _getTT(currentState, symbol - 1);
    }
    return currentState;
}

void AlternativeClassifier::_determineOutput(int *output) {
    for (int i_state = 0; i_state < _statesNum; i_state++) {
        int max_label_index = 0;
        for (int label = 1; label < _labelNum; label++) {
            if (_h[i_state][label] > _h[i_state][max_label_index]) {
                max_label_index = label;
            }
        }
        output[i_state] = max_label_index;
    }
}

Backup AlternativeClassifier::_randomTransitionChange() {
    Backup bu;

    // Save previous data
    bu.index = utils::generateRandomNumber(0, _statesNum * _alphabetSize);
    bu.state = _tt[bu.index];

    // Swap to random state different than previous
    int stateNew;
    do {
        stateNew = utils::generateRandomNumber(0, _statesNum);
    } while (stateNew == bu.state);
    _tt[bu.index] = stateNew;

    return bu;
}

void AlternativeClassifier::_swapOutput(int *pNewOutput) {
    for (int i = 0; i < _statesNum; i++) {
        _o[i] = pNewOutput[i];
    }
}

void AlternativeClassifier::_setTT(int state, int symbol, int val) {
    _tt[symbol * _statesNum + state] = val;
}

int AlternativeClassifier::_getTT(int state, int symbol) {
    return _tt[symbol * _statesNum + state];
}

void AlternativeClassifier::_swapNativeStates(
        std::vector<Language *> *pLanguages,
        int *pOutput) {
    int labelNum = 0;

    for (auto it = pLanguages->begin(); it != pLanguages->end(); ++it) {
        vector<State *> states = _selectAndConvert(labelNum, pOutput);
        (*it)->setStates(states);
        labelNum++;
    }
}

vector<State *> AlternativeClassifier::_selectAndConvert(int label,
                                                         int *pOutput) {
    vector<State *> retVec;

    for (int i = 0; i < _statesNum; i++) {
        if (pOutput[i] == label) {
            State *state = new State(i);
            retVec.push_back(state);
        }
    }

    return retVec;
}

void AlternativeClassifier::_swapForeignStates(
        std::vector<Language *> *pLanguages,
        int *pOutput) {
    for (auto it = pLanguages->begin(); it != pLanguages->end(); ++it) {
        vector<State *> states = _selectAndConvert(FOREIGN_LABEL, pOutput);
        (*it)->setStates(states);
    }
}

void AlternativeClassifier::_calculateAndPrintQualityResults(
        const DFA *bestDFA) {

    std::string trainingInfo = "TRAINING";
    std::string testingInfo = "TESTING";

    quality::_convertWords(_nativeTrainingSet);
    quality::_convertWords(_foreignTrainingSet);
    quality::_convertWords(_nativeTestingSet);
    quality::_convertWords(_foreignTestingSet);

    logger::log(quality::distinctResultsToString(_nativeTrainingSet,
                                                 _foreignTrainingSet,
                                                 (DFA *) bestDFA,
                                                 trainingInfo));
    logger::log(quality::overallResultsToString(_nativeTrainingSet,
                                                _foreignTrainingSet,
                                                (DFA *) bestDFA,
                                                trainingInfo));

    logger::log(quality::distinctResultsToString(_nativeTestingSet,
                                                 _foreignTestingSet,
                                                 (DFA *) bestDFA,
                                                 testingInfo));
    logger::log(quality::overallResultsToString(_nativeTestingSet,
                                                _foreignTestingSet,
                                                (DFA *) bestDFA,
                                                testingInfo));

}

double AlternativeClassifier::_fitness() {
    double fitness = 0;

    // NATIVES
    for (int label = 0; label < _labelNum - 1; label++) {
        vector<Word *> *words = (*_nativeTrainingSet)[label]->getWords();

        for (auto it = words->begin(); it != words->end(); ++it) {
            int local_label = _o[f(*it)];
            if (local_label == label) fitness++;
        }
    }


    // FOREIGN
    for (int i = 0; i < _labelNum - 1; i++) {
        vector<Word *> *words = (*_foreignTrainingSet)[i]->getWords();

        for (auto it = words->begin(); it != words->end(); ++it) {
            int local_label = _o[f(*it)];
            if (local_label == FOREIGN_LABEL) fitness++;
        }
    }

    return fitness / (double) _trainingWordsNum;
}

void AlternativeClassifier::_printInfoAndPlot(double iterTime, int iter) {
    // Save current time
    _totalCompuationalTime += iterTime;

    // Clean previous entry
    for (int i = 0; i < numberOfLinesToReset; i++) {
        cout << "\e[A\r";
    }
    numberOfLinesToReset = 0;
    cout << endl;
    numberOfLinesToReset++;

////    cout << "                         :::::::::::::::::::::::: " << endl;
//    cout << "                         ::::: HILL CLIMBER ::::: " << endl;
////    cout << "                         :::::::::::::::::::::::: " << endl;
//    cout << endl;
//    numberOfLinesToReset+=2;


    cout << "            _  _ _ _ _    ___ _ _       _             " << endl;
    cout << "           | || (_) | |  / __| (_)_ __ | |__  ___ _ _ " << endl;
    cout << "           | __ | | | | | (__| | | '  \\| '_ \\/ -_) '_|" << endl;
    cout << "           |_||_|_|_|_|  \\___|_|_|_|_|_|_.__/\\___|_|  " << endl;
    cout << "                                                      " << endl;
    numberOfLinesToReset += 5;

    cout << "           [Iteration      ]: " << iter << "/" << global_settings::MAX_ITER << endl;
    numberOfLinesToReset++;
    LOG_CALC("Iteration Time ", iterTime);
    numberOfLinesToReset++;
    LOG_CALC("States         ", _statesNum);
    numberOfLinesToReset++;
    LOG_CALC("Classes        ", _labelNum - 1);
    numberOfLinesToReset++;
    LOG_CALC("Alphabet Size  ", _alphabetSize);
    numberOfLinesToReset++;
    LOG_CALC("Training Words ", _trainingWordsNum);
    numberOfLinesToReset++;
    LOG_CALC("Testing Words  ", _wordsNum - _trainingWordsNum);
    numberOfLinesToReset++;
    LOG_CALC("Fitness        ", _currentFitness);
    numberOfLinesToReset++;
    LOG_CALC("Estimated Time ", _estimateTime(iter));
    numberOfLinesToReset++;

    /* ----- MOUNTAINS PICTURE ----- */
    cout << endl;
    cout <<
    "                                /\\                               " <<
    endl;
    cout <<
    "                              //  \\     _      /\\               " <<
    endl;
    cout <<
    "                 /\\_        _//    \\   / \\/\\ _/  \\    /\\    " <<
    endl;
    cout <<
    "               _/   \\/\\   _/ /      \\_/   \\_/     \\__/ _\\   " <<
    endl;
    cout <<
    "              /        `./   \\_      \\_    / //    /    \\\\    " <<
    endl;
    cout <<
    "             //          \\_  / \\       \\  / _     /  /    \\   " <<
    endl;
    cout <<
    "            //             |/                                     " <<
    endl;
    cout << endl << endl;
    numberOfLinesToReset += 10;
}

double AlternativeClassifier::_estimateTime(double iter){
    double averangeIterTime = _totalCompuationalTime / iter;
    double iterationsLeft = global_settings::MAX_ITER - iter;
    return iterationsLeft * averangeIterTime;
}

int AlternativeClassifier::_calculateWordsNum(vector<Language *> *pNatives,
                                              vector<Language *> *pForeigns) {
    int wordsNum = 0;

    for (auto it = pNatives->begin();
         it != pNatives->end(); ++it) {
        wordsNum += (*it)->size();
    }

    for (auto it = pForeigns->begin();
         it != pForeigns->end(); ++it) {
        wordsNum += (*it)->size();
    }

    return wordsNum;
}

void AlternativeClassifier::_logDFA() {
    std::string states = "DFA: \n";
    states += "[FOREIGN_LABEL]: " + to_string(_labelNum-1) + "\n";
    states += "[STATES]: ";
    for(int i = 0; i < _statesNum;i++) {
        states += to_string(_o[i]);
        states += " ";
    }


    logger::log(states);
}
