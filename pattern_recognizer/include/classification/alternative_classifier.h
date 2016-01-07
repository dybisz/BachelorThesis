//
// Created by dybisz on 30.12.15.
//

#ifndef BACHELOR_THESIS_ALTERNATIVE_CLASIFIER_H
#define BACHELOR_THESIS_ALTERNATIVE_CLASIFIER_H

#include <settings/global_settings.h>
#include <gtest/gtest.h>
#include <language.h>
#include <unordered_map>
#include <dfa.h>

using namespace std;


struct Backup {
    int index;
    int state;
};

class AlternativeClassifier {
public:
    static unsigned int FOREIGN_LABEL;

    // Constructor compatible with PSO-based classifier
    AlternativeClassifier(vector<Language *> *nativePatterns,
                          vector<Language *> *foreignPatterns,
                          unsigned int states,
                          unsigned int alphabetSize,
                          double testingSetRatio);

    ~AlternativeClassifier();

    void compute();

private:
    FRIEND_TEST(AlternativeClassifierTest, Allocate_Labeled_Words_Map);

    FRIEND_TEST(AlternativeClassifierTest, Allocate_Transition_Table);

    FRIEND_TEST(AlternativeClassifierTest, Allocate_Smart_State_Table);

    FRIEND_TEST(AlternativeClassifierTest, Compute);

    vector<Language *> *_nativeTrainingSet;
    vector<Language *> *_foreignTrainingSet;
    vector<Language *> *_nativeTestingSet;
    vector<Language *> *_foreignTestingSet;
    unordered_map<int, vector<Word *>> _wordsMap;
    int _alphabetSize;
    int _statesNum;
    int _wordsNum;
    int _trainingWordsNum;
    int _labelNum;
    vector<int> _tt;
    int **_h;
    int *_o;
    double _currentFitness;
    Backup _ttOrigin;
    DFA* _dfa;
    int numberOfLinesToReset = 0;
    // MAP BUSINESS
    void _allocateLabeledWordsMap(vector<Language *> *pNativePatterns,
                                  vector<Language *> *pForeignPatterns,
                                  int &wordsNum, int &labelNum);

    void _assignWordsToLabel(int label, vector<Word *> *pWords);

    void _printLabeledWords();

    string _wordsToString(vector<Word *> words);

    // TT BUSINESS
    void _allocateTransitionTable(int nStates, int nSymbols);

    void _allocateSmartStateTable(int wordsNum, int labelNum);

    void _allocateOutputArray(int nLabel);

    void _randomizeTransitionTable();

    void _computeSmartStates();

    void _zero2DArray(int **array2D, int dim1, int dim2);

    int f(Word *pWord);

    void _determineOutput(int *output);

    Backup _randomTransitionChange();

    void _swapOutput(int *pNewOutput);

    void _setTT(int state, int symbol, int val);

    int _getTT(int x, int y);

    void _swapNativeStates(vector<Language *> *pLanguages, int *pOutput);

    vector<State *> _selectAndConvert(int label, int *pOutput);

    void _swapForeignStates(vector<Language *> *pLanguages, int *pOutput);

    void _calculateAndPrintQualityResults(const DFA* bestDFA);

    double _fitness();
    void _printInfoAndPlot(double d, int i);

    int _calculateWordsNum(vector<Language *> *pNatives,
                           vector<Language *> *pForeigns);
};

#endif //BACHELOR_THESIS_ALTERNATIVE_CLASIFIER_H
