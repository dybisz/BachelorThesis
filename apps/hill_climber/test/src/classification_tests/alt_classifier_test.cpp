//
// Created by dybisz on 30.12.15.
//

#include <gtest/gtest.h>
#include <classification/alternative_classifier.h>
#include <xls_loader.h>
#include <patterns_to_languages.h>

using namespace std;

string _NATIVE_XLS_PATH = "./res/short_Natives.xls";
string _FOREIGN_XLS_PATH = "./res/short_Foreign_90ccl.xls";
AlternativeClassifier *classifier;

/* ----- Settings ----- */
int _PATTERNS_TO_LOAD = 50;
int _LABELS_TO_LOAD = 2;
unsigned int _SYMBOLS_IN_ALPHABET = 7;
unsigned int _STATES = 150;
double _TESTING_SET_RATIO = 0.3;

/* ----- Testing Variables ----- */
int _FOREIGN_LABELS = _LABELS_TO_LOAD;
int _WORDS_IN_TOTAL = _PATTERNS_TO_LOAD * (_LABELS_TO_LOAD + _FOREIGN_LABELS);
int _TRAINING_WORDS = (int)(_WORDS_IN_TOTAL - _TESTING_SET_RATIO * _WORDS_IN_TOTAL);
int _PATTERN_TRAINING_WORDS = (int)(_PATTERNS_TO_LOAD - _TESTING_SET_RATIO * _PATTERNS_TO_LOAD);
int _FOREIGN_TRAINING_WORDS = (int)(_LABELS_TO_LOAD * _PATTERNS_TO_LOAD - _TESTING_SET_RATIO * _LABELS_TO_LOAD * _PATTERNS_TO_LOAD);

/* ----- Auxiliary Methods ----- */
void globalClassifierInit();
void globalClassifierFree();

/* ----------------- */
/* ----- Tests ----- */
/* ----------------- */
/*
TEST(AlternativeClassifierTest, Loaded_Parameters_Check) {
    globalClassifierInit();

    // Words in total
    EXPECT_EQ(_WORDS_IN_TOTAL, classifier->_wordsNum);
    // Words in training set
    EXPECT_EQ(_TRAINING_WORDS, classifier->_trainingWordsNum);
    // Words assign to label '0'
    EXPECT_EQ(_PATTERN_TRAINING_WORDS, (classifier->_wordsMap[0]).size());
    // Words assign to label '1'
    EXPECT_EQ(_PATTERN_TRAINING_WORDS, (classifier->_wordsMap[1]).size());
    // Words assign to label 'FOREIGN'
    EXPECT_EQ(_FOREIGN_TRAINING_WORDS,
              (classifier->_wordsMap[AlternativeClassifier::FOREIGN_LABEL]).size());
    // Number of distinct labels + labels for foreigns
    EXPECT_EQ(_LABELS_TO_LOAD + 1, classifier->_labelNum);

}*/
// TODO columns in _h sum up to _PATTERNS_TO_LOAD test
// TODO when _h and _tt will be one dimensional vectors.
//TEST(AlternativeClassifierTest, Allocate_Transition_Table) {
//
//
//}
//
//TEST(AlternativeClassifierTest, Allocate_Smart_State_Table) {
//
//}

TEST(AlternativeClassifierTest, Compute) {
//    utils::seed();
//    classifier->compute();
    globalClassifierFree();
}

/* ---------------------------------------- */
/* ----- Auxiliary Methods Definition ----- */
/* ---------------------------------------- */

void globalClassifierInit() {
    XlsLoader nativeXLSLoader(_NATIVE_XLS_PATH, _LABELS_TO_LOAD,
                              _PATTERNS_TO_LOAD);
    XlsLoader foreignXLSLoader(_FOREIGN_XLS_PATH, _LABELS_TO_LOAD,
                               _PATTERNS_TO_LOAD);

    // Deleted by XlsLoader class
    vector<Pattern *> *nativePatterns = nativeXLSLoader.getPatterns();
    vector<Pattern *> *foreignPatterns = foreignXLSLoader.getPatterns();

    // Deleted by AlternativeClassifier class
    std::vector<Language *> *nativeLanguages =
            patterns_to_languages::convert(nativePatterns,
                                           _SYMBOLS_IN_ALPHABET);
    std::vector<Language *> *foreignLanguages =
            patterns_to_languages::convert(foreignPatterns,
                                           _SYMBOLS_IN_ALPHABET);

    classifier = new AlternativeClassifier(
            nativeLanguages,
            foreignLanguages,
            _STATES,
            _SYMBOLS_IN_ALPHABET,
            _TESTING_SET_RATIO);

}

void globalClassifierFree() {
    delete classifier;
}