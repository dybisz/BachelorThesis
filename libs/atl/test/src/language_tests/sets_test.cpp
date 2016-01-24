//
// Created by dybisz on 26.12.15.
//

#include <gtest/gtest.h>
#include <language/language.h>
#include <xls_loader.h>
#include "classes_to_languages.h"
#include <language/sets_disassociation.h>

using namespace std;

string NATIVE_SHORT = "./res/short_Natives.xls";
string FOREIGN_SHORT = "./res/short_Foreign_90ccl.xls";
int ALPHABET = 4;
int STATES_NATIVE = 2;
int STATES_FOREIGN = 2;
vector<Language *> *nLanguages;
vector<Language *> *fLanguages;

void auxInit();

void auxRelease();

/* ----------------- */
/* ----- TESTS ----- */
/* ----------------- */

TEST(SetsTest, Detach_Invalid_Arguments) {
    auxInit();
    ASSERT_ANY_THROW(set_disassociation::detachWords(-1, nLanguages));
    ASSERT_ANY_THROW(set_disassociation::detachWords(2, nLanguages));
    auxRelease();
}

TEST(SetsTest, Words_Count) {
    auxInit();
    double subsetRatio = 0.3;

    int s0_count = (*nLanguages)[0]->size();
    int s1_count = (*nLanguages)[1]->size();

    int t0_count = s0_count * subsetRatio;
    int t1_count = s1_count * subsetRatio;

    int n_s0_count = s0_count - t0_count;
    int n_s1_count = s1_count - t1_count;

    vector<Language *> *trainingSet = set_disassociation::detachWords(
            subsetRatio, nLanguages);

    EXPECT_EQ(t0_count, (*trainingSet)[0]->size());
    EXPECT_EQ(t0_count, (*trainingSet)[1]->size());
    EXPECT_EQ(n_s0_count, (*nLanguages)[0]->size());
    EXPECT_EQ(n_s1_count, (*nLanguages)[1]->size());

    delete trainingSet;
    auxRelease();
}

/* --------------------------------- */
/* ----- AUXILIARY DEFINITIONS ----- */
/* --------------------------------- */

void auxInit() {
    XlsLoader nativeXLSLoader(NATIVE_SHORT);
    XlsLoader foreignXLSLoader(FOREIGN_SHORT);

    vector<Class *> *nativePatterns = nativeXLSLoader.getClasses();
    vector<Class *> *foreignPatterns = foreignXLSLoader.getClasses();

    nLanguages =
            patterns_to_languages::convert(
                    nativePatterns,
                    STATES_NATIVE,
                    ALPHABET);

    fLanguages =
            patterns_to_languages::convert(
                    foreignPatterns,
                    STATES_FOREIGN,
                    ALPHABET,
                    STATES_NATIVE);
}

void auxRelease() {
    for (unsigned int i = 0; i < nLanguages->size(); i++)
        delete (*nLanguages)[i];
    for (unsigned int i = 0; i < fLanguages->size(); i++)
        delete (*fLanguages)[i];

    delete nLanguages;
    delete fLanguages;
}