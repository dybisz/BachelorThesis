//
// Created by dybisz on 20.12.15.
//

#include <language/alphabet.h>
#include <patterns_to_languages.h>

vector<Language *> *patterns_to_languages::convert(
        vector<Pattern *> *patterns,
        int numberOfStates,
        int precision,
        int stateStartingIndex) {
    _checkConditions(numberOfStates, precision, patterns);

    vector<Language *> *languages = NULL;
    try {
        vector<Interval *> intervals = _calculateFeaturesIntervals(patterns);
        vector<Pattern *> *normalized = _normalizePatterns(patterns, intervals);
        Alphabet *alphabet = new Alphabet(precision);
        languages = _createLanguages(normalized, alphabet, numberOfStates,
                                     stateStartingIndex);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

    return languages;
}

Language* patterns_to_languages::convert(Pattern& pattern, int precision) {

    std::vector<Pattern*> patternVector;
    patternVector.push_back(&pattern);

    std::vector<Language*>* languageVector = convert(&patternVector, precision);

    Language* convertedLanguage = (*languageVector)[0];

    delete languageVector;

    return convertedLanguage;
}


vector<Language *> *patterns_to_languages::convert(vector<Pattern *> *patterns,
                                                   int precision) {
    _checkConditions(1, precision, patterns);

    vector<Language *> *languages = NULL;
    try {
        vector<Interval *> intervals = _calculateFeaturesIntervals(patterns);
        vector<Pattern *> *normalized = _normalizePatterns(patterns, intervals);
        Alphabet *alphabet = new Alphabet(precision); // TODO memory leak
        languages = _createLanguages(normalized, alphabet);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
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
        vector<Pattern *> *pPattern, Alphabet *pAlphabet, int numberOfStates,
        int stateStartingIndex) {

    vector<Language *> *languages = new vector<Language *>();
    int stateCounter = stateStartingIndex;

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


vector<Language *> *patterns_to_languages::_createLanguages(
        vector<Pattern *> *pPattern, Alphabet *pAlphabet) {

    vector<Language *> *languages = new vector<Language *>();

    for (auto iter = pPattern->begin(); iter != pPattern->end(); ++iter) {

        Language *language = new Language((*iter), (*pAlphabet));
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

vector<Word *> *patterns_to_languages::_convertPatternsToWords(
        vector<Pattern *> *pPatterns, Alphabet *alphabet) {

    vector<Word *> *words = new vector<Word *>();

    // Consider each pattern
    for (auto pattIt = pPatterns->begin();
         pattIt != pPatterns->end(); ++pattIt) {

        // Acquire pattern's features vectors
        vector<FeaturesVector *> *features = (*pattIt)->getFeatures();

        // For each features vector
        for (auto fvIt = features->begin(); fvIt != features->end(); ++fvIt) {
            Word *word = new Word();
            word = _convertFeatureToWord((*fvIt), alphabet);
            // Save word
            words->push_back(word);
        }
    }

    return words;
}

Word *patterns_to_languages::_convertFeatureToWord(
        FeaturesVector *pFeatureVector,
        Alphabet *pAlphabet) {
    Word *word = new Word();

    for (int i = 0; i < pFeatureVector->size(); ++i) {
        double entry = (*pFeatureVector)[i];
        Symbol *symbol = new Symbol(pAlphabet->convertToSymbol(entry));
        (*word) + symbol;
    }

    return word;
}

void patterns_to_languages::_checkConditions(int states, int precision,
                                             vector<Pattern *> *patterns) {
    if (patterns == NULL) {
        throw invalid_argument(
                "pointer to patters is NULL");
    }

    if (states < 1) {
        throw invalid_argument(
                "numberOfStates < 1");
    }

    if (precision < 1) {
        throw invalid_argument(
                "precision < 1");
    }
}