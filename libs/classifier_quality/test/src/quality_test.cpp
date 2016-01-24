//
// Created by dybisz on 23.12.15.
//

#include <gtest/gtest.h>
#include <automata/transition/transition_function.h>
#include <vector>
#include <automata/dfa.h>
#include <xls_loader.h>
#include <language/language.h>
#include <transformation/transformation.h>
#include "classifier_quality.h"

using namespace std;

/* ----- QUALITY TESTS SETTINGS ----- */
string SHORT_NATIVE = "./res/short_Natives.xls";
string SHORT_FOREIGN = "./res/short_Foreign_90ccl.xls";
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
double NATIVE_WORDS = 201;
double FOREIGN_WORDS = 201;
double TP_DISTINCT_COUNT = 101;
double TP_OVERALL_COUNT = 105;
double FN_DISTINCT_COUNT = 100;
double FN_OVERALL_COUNT = 96;
double FP_DISTINCT_COUNT = 102;
double FP_OVERALL_COUNT = 5;
double TN_DISTINCT_COUNT = 99;
double TN_OVERALL_COUNT = 196;

/* ----- INIT/DELETE GLOBAL DATA ----- */
void initGlobals();

void releaseGlobals();

/* ----------------- */
/* ----- TESTS ----- */
/* ----------------- */

TEST(QualityTest, Native_Words_Count) {
    /* ----- INIT DATA ----- */
    initGlobals();

    EXPECT_EQ(NATIVE_WORDS, quality::_countNumberOfWords(nativeLanguages));
}

TEST(QualityTest, Foreign_Words_Count) {

    EXPECT_EQ(FOREIGN_WORDS, quality::_countNumberOfWords(foreignLanguages));
}

/* ----- TRUE POSITIVES ----- */

TEST(QualityTest, Count_TP_Distinct) {

    EXPECT_EQ(NATIVE_WORDS - FN_DISTINCT_COUNT,
              quality::numberOfTrueDistinct(nativeLanguages,
                                            dfa));
}

TEST(QualityTest, Count_TP_Overall) {

    EXPECT_EQ(NATIVE_WORDS - FN_OVERALL_COUNT,
              quality::numberOfTrueOverall(nativeLanguages,
                                           dfa));
}

TEST(QualityTest, Percentage_TP_Distinct) {

    EXPECT_EQ(TP_DISTINCT_COUNT / NATIVE_WORDS,
              quality::percentageTrueDistinct(nativeLanguages,
                                              dfa));
}

TEST(QualityTest, Percentage_TP_Overall) {

    EXPECT_EQ(TP_OVERALL_COUNT / NATIVE_WORDS,
              quality::percentageTrueOverall(nativeLanguages,
                                             dfa));
}

/* ----- FALSE NEGATIVES ----- */

TEST(QualityTest, Count_FN_Distinct) {

    EXPECT_EQ(NATIVE_WORDS - TP_DISTINCT_COUNT,
              quality::numberOfFalseDistinct(nativeLanguages,
                                             dfa));
}

TEST(QualityTest, Count_FN_Overall) {

    EXPECT_EQ(NATIVE_WORDS - TP_OVERALL_COUNT,
              quality::numberOfFalseOverall(nativeLanguages,
                                            dfa));
}

TEST(QualityTest, Percentage_FN_Distinct) {

    EXPECT_EQ(FN_DISTINCT_COUNT / NATIVE_WORDS,
              quality::percentageFalseDistinct(nativeLanguages,
                                               dfa));
}

TEST(QualityTest, Percentage_FN_Overall) {

    EXPECT_EQ(FN_OVERALL_COUNT / NATIVE_WORDS,
              quality::percentageFalseOverall(nativeLanguages,
                                              dfa));
}

/* ----- FALSE POSITIVES ----- */

TEST(QualityTest, Count_FP_Distinct) {

    EXPECT_EQ(FOREIGN_WORDS - TN_DISTINCT_COUNT,
              quality::numberOfFalseDistinct(foreignLanguages,
                                             dfa));
}

TEST(QualityTest, Count_FP_Overall) {

    EXPECT_EQ(FOREIGN_WORDS - TN_OVERALL_COUNT,
              quality::numberOfFalseOverall(foreignLanguages,
                                            dfa));
}

TEST(QualityTest, Percentage_FP_Distinct) {

    EXPECT_EQ(FP_DISTINCT_COUNT / FOREIGN_WORDS,
              quality::percentageFalseDistinct(foreignLanguages,
                                               dfa));

}

TEST(QualityTest, Percentage_FP_Overall) {

    EXPECT_EQ(FP_OVERALL_COUNT / FOREIGN_WORDS,
              quality::percentageFalseOverall(foreignLanguages,
                                              dfa));
}

/* ----- TRUE NEGATIVES ----- */

TEST(QualityTest, Count_TN_Distinct) {

    EXPECT_EQ(FOREIGN_WORDS - FP_DISTINCT_COUNT,
              quality::numberOfTrueDistinct(foreignLanguages,
                                            dfa));
}

TEST(QualityTest, Count_TN_Overall) {

    EXPECT_EQ(FOREIGN_WORDS - FP_OVERALL_COUNT,
              quality::numberOfTrueOverall(foreignLanguages,
                                           dfa));
}

TEST(QualityTest, Percentage_TN_Distinct) {

    EXPECT_EQ(TN_DISTINCT_COUNT / FOREIGN_WORDS,
              quality::percentageTrueDistinct(foreignLanguages,
                                              dfa));
}

TEST(QualityTest, Percentage_TN_Overall) {

    EXPECT_EQ(TN_OVERALL_COUNT / FOREIGN_WORDS,
              quality::percentageTrueOverall(foreignLanguages,
                                             dfa));
}

/* ----- ACCURACY ----- */

TEST(QualityTest, Accuracy_Distinct) {

    double accuracy = (TP_DISTINCT_COUNT + TN_DISTINCT_COUNT) /
                      (TP_DISTINCT_COUNT + TN_DISTINCT_COUNT +
                       FP_DISTINCT_COUNT + FN_DISTINCT_COUNT);

    EXPECT_EQ(accuracy, quality::calculateAccuracyDistinct(nativeLanguages,
                                                           foreignLanguages,
                                                           dfa));
}

TEST(QualityTest, Accuracy_Overall) {

    double accuracy = (TP_OVERALL_COUNT + TN_OVERALL_COUNT) /
                      (TP_OVERALL_COUNT + TN_OVERALL_COUNT +
                       FP_OVERALL_COUNT + FN_OVERALL_COUNT);

    EXPECT_EQ(accuracy, quality::calculateAccuracyOverall(nativeLanguages,
                                                          foreignLanguages,
                                                          dfa));
}

/* ----- SENSITIVITY ----- */

TEST(QualityTest, Sensitivity_Distinct) {

    double sensitivity = TP_DISTINCT_COUNT /
                         (TP_DISTINCT_COUNT + FN_DISTINCT_COUNT);

    EXPECT_EQ(sensitivity,
              quality::calculateSensitivityDistinct(nativeLanguages,
                                                    foreignLanguages,
                                                    dfa));
}

TEST(QualityTest, Sensitivity_Overall) {

    double sensitivity = TP_OVERALL_COUNT /
                         (TP_OVERALL_COUNT + FN_OVERALL_COUNT);

    EXPECT_EQ(sensitivity, quality::calculateSensitivityOverall(nativeLanguages,
                                                                foreignLanguages,
                                                                dfa));
}

/* ----- PRECISION----- */

TEST(QualityTest, Precision_Distinct) {

    double precision = TP_DISTINCT_COUNT /
                       (TP_DISTINCT_COUNT + FP_DISTINCT_COUNT);

    EXPECT_EQ(precision, quality::calculatePrecisionDistinct(nativeLanguages,
                                                             foreignLanguages,
                                                             dfa));
}

TEST(QualityTest, Precision_Overall) {

    double precision = TP_OVERALL_COUNT /
                       (TP_OVERALL_COUNT + FP_OVERALL_COUNT);

    EXPECT_EQ(precision, quality::calculatePrecisionOverall(nativeLanguages,
                                                            foreignLanguages,
                                                            dfa));
}

/* ----- F-MEASURE----- */

TEST(QualityTest, FMeasure_Distinct) {

    double sensitivity = TP_DISTINCT_COUNT /
                         (TP_DISTINCT_COUNT + FN_DISTINCT_COUNT);
    double precision = TP_DISTINCT_COUNT /
                       (TP_DISTINCT_COUNT + FP_DISTINCT_COUNT);
    double FMeasure = 2.0 * (precision * sensitivity) / (precision + sensitivity);

    EXPECT_EQ(FMeasure, quality::calculateFMeasureDistinct(nativeLanguages,
                                                            foreignLanguages,
                                                            dfa));
}

TEST(QualityTest, FMeasure_Overall) {

    double sensitivity = TP_OVERALL_COUNT /
                         (TP_OVERALL_COUNT + FN_OVERALL_COUNT);
    double precision = TP_OVERALL_COUNT /
                       (TP_OVERALL_COUNT + FP_OVERALL_COUNT);
    double FMeasure = 2.0 * (precision * sensitivity) / (precision + sensitivity);

    EXPECT_EQ(FMeasure, quality::calculateFMeasureOverall(nativeLanguages,
                                                           foreignLanguages,
                                                           dfa));
}

TEST(QualityTest, Summary_Print) {
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

    vector<Class *> *nativePatterns = nativeXLSLoader.getClasses();
    vector<Class *> *foreignPatterns = foreignXLSLoader.getClasses();

    nativeLanguages =
            transformation::convert(
                    nativePatterns,
                    STATES_PER_NATIVE,
                    ALPHABET_SIZE);

    foreignLanguages =
            transformation::convert(
                    foreignPatterns,
                    STATES_PER_FOREIGN,
                    ALPHABET_SIZE,
                    STATES_PER_NATIVE);

    // CONVERT WORDS - WILL BE CHANGED // TODO TODO !!!
    quality::_convertWords(nativeLanguages);
    quality::_convertWords(foreignLanguages);
}

void releaseGlobals() {
    for (unsigned int i = 0; i < nativeLanguages->size(); i++)
        delete (*nativeLanguages)[i];
    for (unsigned int i = 0; i < foreignLanguages->size(); i++)
        delete (*foreignLanguages)[i];

    delete nativeLanguages;
    delete foreignLanguages;
    delete dfa;
}