//
// Created by dybisz on 30.12.15.
//

#include <gtest/gtest.h>
#include <alternative_classifier.h>
#include <loaders/xls_loader.h>
#include <patterns_to_languages.h>
#include <utils.h>

using namespace std;

string _NATIVE_XLS_PATH = "./res/Natives.xls";
string _FOREIGN_XLS_PATH = "./res/Foreign_90ccl.xls";
AlternativeClassifier *classifier;

/* ----- Settings ----- */
int _PATTERNS_TO_LOAD = 750;
int _LABELS_TO_LOAD = 4;
int _SYMBOLS_IN_ALPHABET = 7;
int _STATES =150;
double _TESTING_SET_RATIO = 0.3;

void globalClassifierInit();
void globalClassifierFree();

TEST(AlternativeClassifierTest, Allocate_Labeled_Words_Map) {
    globalClassifierInit();

//    // Words in total
//    EXPECT_EQ(200, classifier->_trainingWordsNum);
//    // Words assign to label '0'
//    EXPECT_EQ(50, (classifier->_wordsMap[0]).size());
//    // Words assign to label '1'
//    EXPECT_EQ(50, (classifier->_wordsMap[1]).size());
//    // Words assign to label 'FOREIGN'
//    EXPECT_EQ(100, (classifier->_wordsMap[AlternativeClassifier::FOREIGN_LABEL]).size());
//    // Number of distinct labels
//    EXPECT_EQ(_LABELS_TO_LOAD, classifier->_labelNum);

}
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
//    globalClassifierFree();
}

void globalClassifierInit() {
//    cout << "[_PATTERNS_TO_LOAD]: " << _PATTERNS_TO_LOAD << endl;
//    cout << "[_LABELS_TO_LOAD]: " << _LABELS_TO_LOAD << endl;
//    cout << "[_STATES]: " << _STATES << endl;
//
//    XlsLoader nativeXLSLoader(_NATIVE_XLS_PATH, _LABELS_TO_LOAD, _PATTERNS_TO_LOAD);
//    XlsLoader foreignXLSLoader(_FOREIGN_XLS_PATH, _LABELS_TO_LOAD, _PATTERNS_TO_LOAD);
//
//    // Deleted by XlsLoader class
//    vector<Pattern *> *nativePatterns = nativeXLSLoader.getPatterns();
//    vector<Pattern *> *foreignPatterns = foreignXLSLoader.getPatterns();
//
//    // Deleted by AlternativeClassifier class
//    std::vector<Language *> *nativeLanguages =
//            patterns_to_languages::convert(nativePatterns,
//                                           _SYMBOLS_IN_ALPHABET);
//    std::vector<Language *> *foreignLanguages =
//            patterns_to_languages::convert(foreignPatterns,
//                                           _SYMBOLS_IN_ALPHABET);
//
//    classifier = new AlternativeClassifier(
//            nativeLanguages,
//            foreignLanguages,
//            _STATES,
//            _SYMBOLS_IN_ALPHABET,
//            _TESTING_SET_RATIO);

}

void globalClassifierFree() {
//    delete classifier;
}