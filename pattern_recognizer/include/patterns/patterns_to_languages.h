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
#include <stdexcept>

using namespace std;

/*
 * When data have been loaded, they are in form of the features vectors
 * with assigns labels, hence they represents patterns. In our application
 * tough we consider input data as a words over some alphabet, which will be
 * later on processed by an automaton. That is why we produce languages with
 * accepting states attached to them // TODO we can change this retarded descr.
 */
namespace patterns_to_languages {

    // Converts patterns to languages. Second argument represents number of
    // accepting states per language. For now, we assume that this number is
    // equal for all alnguages. Third argument, decides how many letters
    // are in alphabet, which corresponds 1-1 with precision of coding.
    vector<Language *> *convert(vector<Pattern *> *patterns, int numberOfStates,
                                int precision);

    // Auxiliary method. It returns vector of intervals, where i'th entry
    // represents <min;max> interval of i'th feature.
    // WARNING: vector contains pointers, which must be freed after usage.
    vector<Interval *> _calculateFeaturesIntervals(
            vector<Pattern *> *pPatterns);

    // Having min/max interval for each feature, method will normalize every
    // entry to be from interval <0;1>
    vector<Pattern *> * _normalizePatterns(vector<Pattern *> *pPatterns,
                                           vector<Interval *> pInterval);

    // TODO
    vector<Language *> *_createLanguages(vector<Pattern *> *pPattern,
                                         Alphabet *pAlphabet, int numberOfStates);

    // During debuging process it is really nice to have method printing
    // out collective intervals values. Useful especially in unit tests.
    string _vectorOfIntervalsToString(vector<Interval *> &interval);
}

#endif //BACHELOR_THESIS_PATTERNS_TO_LANGUAGES_H
