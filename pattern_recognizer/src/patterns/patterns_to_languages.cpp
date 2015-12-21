//
// Created by dybisz on 20.12.15.
//

#include <alphabet.h>
#include <logger.h>
#include "patterns_to_languages.h"


vector<Language *> *patterns_to_languages::convert(vector<Pattern *> *patterns,
                                                   int numberOfStates,
                                                   int precision) {
    // TODO check for dumb values
    vector<Language *> *languages = NULL;
    try {
        vector<Interval *> intervals = _calculateFeaturesIntervals(patterns);
        vector<Pattern *> *normalized = _normalizePatterns(patterns, intervals);
        Alphabet *alphabet = new Alphabet(precision);
        // jezyk przyjmuje slowa, nie patterny
        languages = _createLanguages(normalized, alphabet, numberOfStates);
    }
    catch (std::exception &e) {
        LOG_ERROR(e.what())
    }

    return languages;
}

vector<Interval *> patterns_to_languages::_calculateFeaturesIntervals(
        vector<Pattern *> *pPatterns) {

    vector<Interval *> intervals;
    int numberOfFeatures = (*pPatterns)[0]->getVector(0)->size();

    for (int feature = 0; feature < numberOfFeatures; feature++) {

        // Init min/max values
        double min = INT32_MAX;
        double max = INT32_MIN;

        // Iterate through all provided patterns.
        for (auto iter = pPatterns->begin(); iter != pPatterns->end(); ++iter) {

            // Gather min.max values from particular pattern
            double localMin = (*iter)->getFeatureMin(feature);
            double localMax = (*iter)->getFeatureMax(feature);

            // Check conditions
            if (localMin < min) min = localMin;
            if (localMax > max) max = localMax;

        }

        // Update intervals
        Interval *interval = new Interval(min, max);
        intervals.push_back(interval);
    }

    return intervals;
}

vector<Pattern *> *patterns_to_languages::_normalizePatterns(
        vector<Pattern *> *pPatterns,
        vector<Interval *> intervals) {

    int numberOfFeatures = (*pPatterns)[0]->getVector(0)->size();
    vector<FeaturesVector *> *features;

    // Iterate through all provided patterns
    for (auto iter = pPatterns->begin(); iter != pPatterns->end(); ++iter) {

        features = (*iter)->getFeatures();
        for (auto iter1 = features->begin();
             iter1 != features->end(); ++iter1) {

            for (int i = 0; i < numberOfFeatures; i++) {

                // Additional calculations
                double value = (*(*iter1))[i];
                double nominator = value - intervals[i]->getLBound();
                double denominator =
                        intervals[i]->getRBound() - intervals[i]->getLBound();
                double result = (nominator / denominator);

                // Swap values
                (*iter1)->setEntry(i, result);

                if (result > 1) {
                    throw invalid_argument(
                            "Entry > 1 in normalization process");
                }
            }

        }

    }
    return pPatterns;
}

vector<Language *> *patterns_to_languages::_createLanguages(
        vector<Pattern *> *pPattern,
        Alphabet *pAlphabet, int numberOfStates) {

    vector<Language *> *languages = new vector<Language *>();
    int stateCounter = 0;

    for (auto iter = pPattern->begin(); iter != pPattern->end(); ++iter) {

        vector<State *> states;
        int aux = numberOfStates;

        // Fill up states with unique markings
        while (aux--) {
            State *state = new State(stateCounter);
            states.push_back(state);
            stateCounter++;
        }

        Language *language = new Language((*iter), (*pAlphabet), states);
        languages->push_back(language);
    }

    return languages;
}

string patterns_to_languages::_vectorOfIntervalsToString(
        vector<Interval *> &interval) {
    string out = "intervals: \n";
    int i = 0;
    for (auto iter = interval.begin(); iter != interval.end(); ++iter) {
        out += "[";
        out += to_string(i++);
        out += "] : ";
        out += (*iter)->toString();
        out += "\n";
    }
    out += "\n";
    return out;
}
