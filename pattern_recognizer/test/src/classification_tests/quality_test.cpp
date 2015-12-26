//
// Created by dybisz on 23.12.15.
//

#include <gtest/gtest.h>
#include <transition_function.h>
#include <vector>
#include <dfa.h>
#include <loaders/xls_loader.h>
#include <language.h>
#include <patterns_to_languages.h>
#include <classifier.h>
#include <quality.h>

using namespace std;

/* ----- QUALITY TESTS SETTINGS ----- */
string SHORT_NATIVE = "./res/short_Natives.xls";
string SHORT_FOREIGN = "./res/short_Foreign_90ccl.xls";
int ALPHABET_SIZE = 4;
int STATES_PER_NATIVE = 2;
int STATES_PER_FOREIGN = 2;

void free_patterns(vector<Pattern *> *pPatters);

// WARNING: test has hardcoded entries for DFA. Entries are based on PSO with
// 6 states, 4 symbols and ~0.7 accuracy.
TEST(QualityTest, Foo) {
    vector<int> entries = {
            3, 0, 0, 1, 3, 0,
            1, 0, 0, 0, 1, 5,
            5, 5, 2, 5, 4, 5,
            4, 3, 5, 5, 5, 5,
    };
    TransitionFunction *tf = new TransitionFunction(6, 4, entries);
    DFA *dfa = new DFA(tf);

    XlsLoader nativeXLSLoader(SHORT_NATIVE);
    XlsLoader foreignXLSLoader(SHORT_FOREIGN);

    vector<Pattern *> *nativePatterns = nativeXLSLoader.getPatterns();
    vector<Pattern *> *foreignPatterns = foreignXLSLoader.getPatterns();

    vector<Language *> *nativeLanguages =
            patterns_to_languages::convert(
                    nativePatterns,
                    STATES_PER_NATIVE,
                    ALPHABET_SIZE);

    vector<Language *> *foreignLanguages =
            patterns_to_languages::convert(
                    foreignPatterns,
                    STATES_PER_FOREIGN,
                    ALPHABET_SIZE,
                    STATES_PER_NATIVE);

    // CONVERT WORDS - WILL BE CHANGED
    quality::_convertWords(nativeLanguages);
    quality::_convertWords(foreignLanguages);


    // COMPUTE TP
    cout << "TP_DISTINCT count: " << quality::computeTPDistinct(nativeLanguages,
                                                               foreignLanguages,
                                                               dfa) << endl;
    cout << "TP_OVERALL  count: " << quality::computeTPOverall(nativeLanguages,
                                                                foreignLanguages,
                                                                dfa) << endl;

    /* ----- FREE DATA ----- */
    // classifier correctly frees languages.
    Classifier *classifier = new Classifier(
            nativeLanguages,
            foreignLanguages,
            STATES_PER_NATIVE,
            STATES_PER_FOREIGN,
            ALPHABET_SIZE);
    delete classifier;
    delete dfa;
}

