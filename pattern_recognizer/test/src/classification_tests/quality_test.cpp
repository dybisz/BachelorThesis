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
int ALL_WORDS = 402;
int ALPHABET_SIZE = 4;
int STATES_PER_NATIVE = 2;
int STATES_PER_FOREIGN = 2;


/* ----- GLOBAL DFA ----- */
vector<int> entries = {
        3, 0, 0, 1, 3, 0,
        1, 0, 0, 0, 1, 5,
        5, 5, 2, 5, 4, 5,
        4, 3, 5, 5, 5, 5,
};
TransitionFunction *tf;
DFA *dfa;
vector<Language *> *nativeLanguages;
vector<Language *> *foreignLanguages;


/* ----- EXPECTED RESULTS ----- */
double TP_DISTINCT_COUNT = 200;
double TP_OVERALL_COUNT = 297;
double FN_DISTINCT_COUNT = 202;
double FN_OVERALL_COUNT = 105;

/* ----- INIT/DELETE GLOBAL DATA ----- */
void initGlobals();

void releaseGlobals();

/* ----------------- */
/* ----- TESTS ----- */
/* ----------------- */

TEST(QualityTest, Words_Loaded) {
    /* ----- INIT DATA ----- */
    initGlobals();

    EXPECT_EQ(ALL_WORDS, quality::_countNumberOfWords(nativeLanguages) +
                         quality::_countNumberOfWords(foreignLanguages));
}

TEST(QualityTest, Count_TP_Distinct) {

    EXPECT_EQ(ALL_WORDS - FN_DISTINCT_COUNT,
              quality::_numberOfTPDistinct(nativeLanguages,
                                           foreignLanguages,
                                           dfa));
}

TEST(QualityTest, Count_TP_Overall) {

    EXPECT_EQ(ALL_WORDS - FN_OVERALL_COUNT,
              quality::_numberOfTPOverall(nativeLanguages,
                                          foreignLanguages,
                                          dfa));
}

TEST(QualityTest, Percentage_TP_Distinct) {

    EXPECT_EQ(TP_DISTINCT_COUNT / ALL_WORDS,
              quality::computeTPDistinct(nativeLanguages,
                                         foreignLanguages,
                                         dfa));
}

TEST(QualityTest, Percentage_TP_Overall) {

    EXPECT_EQ(TP_OVERALL_COUNT / ALL_WORDS,
              quality::computeTPOverall(nativeLanguages,
                                        foreignLanguages,
                                        dfa));
}

TEST(QualityTest, Count_FN_Distinct) {

    EXPECT_EQ(ALL_WORDS - TP_DISTINCT_COUNT,
              quality::_numberOfFNDistinct(nativeLanguages,
                                           foreignLanguages,
                                           dfa));
}

TEST(QualityTest, Count_FN_Overall) {

    EXPECT_EQ(ALL_WORDS - TP_OVERALL_COUNT,
              quality::_numberOfFNOverall(nativeLanguages,
                                          foreignLanguages,
                                          dfa));
}

TEST(QualityTest, Percentage_FN_Distinct) {

    EXPECT_EQ(FN_DISTINCT_COUNT / ALL_WORDS,
              quality::computeFNDistinct(nativeLanguages,
                                         foreignLanguages,
                                         dfa));
}

TEST(QualityTest, Percentage_FN_Overall) {

    EXPECT_EQ(FN_OVERALL_COUNT / ALL_WORDS,
              quality::computeFNOverall(nativeLanguages,
                                        foreignLanguages,
                                        dfa));
    /* ----- FREE DATA ----- */
    releaseGlobals();
}
/* --------------------------------- */
/* ----- AUXILIARY DEFINITIONS ----- */
/* --------------------------------- */

void initGlobals() {
    tf = new TransitionFunction(6, 4, entries);
    dfa = new DFA(tf);
    XlsLoader nativeXLSLoader(SHORT_NATIVE);
    XlsLoader foreignXLSLoader(SHORT_FOREIGN);

    vector<Pattern *> *nativePatterns = nativeXLSLoader.getPatterns();
    vector<Pattern *> *foreignPatterns = foreignXLSLoader.getPatterns();

    nativeLanguages =
            patterns_to_languages::convert(
                    nativePatterns,
                    STATES_PER_NATIVE,
                    ALPHABET_SIZE);

    foreignLanguages =
            patterns_to_languages::convert(
                    foreignPatterns,
                    STATES_PER_FOREIGN,
                    ALPHABET_SIZE,
                    STATES_PER_NATIVE);

    // CONVERT WORDS - WILL BE CHANGED // TODO TODO !!!
    quality::_convertWords(nativeLanguages);
    quality::_convertWords(foreignLanguages);
}

void releaseGlobals() {
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