//
// Created by dybisz on 20.12.15.
//

#ifndef BACHELOR_THESIS_PATTERNS_TO_LANGUAGES_H
#define BACHELOR_THESIS_PATTERNS_TO_LANGUAGES_H

#include <vector>
#include <interval.h>
#include <string>
#include <language.h>
#include <pattern.h>

using namespace std;

/*
 * When data have been loaded, they are in form of the features vectors
 * with assigns labels, hence they represents patterns. In our application
 * tough we consider input data as a words over some alphabet, which will be
 * later on processed by an automaton. That is why we produce languages with
 * accepting states attached to them // TODO we can change this retarded descr.
 */
namespace patterns_to_languages {

    /* ----------------------- */
    /* -----MAIN METHODS ----- */
    /* ----------------------- */

    // Converts patterns to languages. Second argument represents number of
    // accepting states per language. For now, we assume that this number is
    // equal for all languages. Third argument, decides how many letters
    // are in alphabet, which corresponds 1-1 with precision of coding.
    // Last but not list, one encounters additional parameter with defualt
    // value equal to 0. It tells converter from which state index it should
    // start numbering states related to loaded language. Very useful, when we
    // e.g need to consecutively load 2 languages and preserve different state
    // numbering.
    vector<Language *> *convert(vector<Pattern *> *patterns, int numberOfStates,
                                int precision, int stateStartingIndex = 0);

    vector<Language *> *convert(vector<Pattern *> *patterns, int precision);

    // Auxiliary method. It returns vector of intervals, where i'th entry
    // represents <min;max> interval of i'th feature.
    // WARNING: vector contains pointers, which must be freed after usage.
    vector<Interval *> _calculateFeaturesIntervals(
            vector<Pattern *> *pPatterns);

    // Having min/max interval for each feature, method will normalize every
    // entry to be from interval <0;1>
    vector<Pattern *> *_normalizePatterns(vector<Pattern *> *pPatterns,
                                          vector<Interval *> pInterval);

    // WARNING: input data must be normalized
    // Intermediate conversion has been provide to elevate flexibility of this
    // namespace. Now, one can create distinct set of words (based on patterns)
    // and do whatever he/she wants with it.
    // Output data is just a vector of words created from all features vectors
    // hidden in provided patterns.
    vector<Word *> *_convertPatternsToWords(vector<Pattern *> *pPatterns,
                                            Alphabet *alphabet);

    vector<Language *> *_createLanguages(vector<Pattern *> *pPattern,
                                         Alphabet *pAlphabet,
                                         int numberOfStates,
                                         int stateStartingIndex);

    // Creates languages based on the patterns and alphabet
    vector<Language *> *_createLanguages(vector<Pattern *> *pPattern,
                                            Alphabet *pAlphabet);
    /* --------------------- */
    /* ----- AUXILIARY ----- */
    /* --------------------- */

    // During debugging process it is really nice to have method printing
    // out collective intervals values. Useful especially in unit tests.
    string _vectorOfIntervalsToString(vector<Interval *> &interval);

    // Additional method for changing single feature vector to a word over
    // specified alphabet.
    Word *_convertFeatureToWord(FeaturesVector *pFeatureVector,
                                Alphabet *pAlphabet);

    // Method throws exception when states or precision is < 1,
    // or pointer to patterns is NULL
    void _checkConditions(int states, int precision,
                          vector<Pattern *> *patterns);


}

#endif //BACHELOR_THESIS_PATTERNS_TO_LANGUAGES_H
