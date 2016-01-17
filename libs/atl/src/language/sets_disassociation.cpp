//
// Created by dybisz on 26.12.15.
//

#include <language/sets_disassociation.h>

vector<Language *> *set_disassociation::detachWords(double subsetSetRatio,
                                                    vector<Language *> *baseSet) {
    vector<Language *> *subset = new vector<Language *>();

    if (subsetSetRatio < 0 || subsetSetRatio > 1) {
        throw std::invalid_argument(
                "testingSetRation must be from <0;1> interval.");
    }

    for (auto lang = baseSet->begin(); lang != baseSet->end(); ++lang) {
        vector<Word *> subsetWords;
        int outputSize = (*lang)->size() * subsetSetRatio;

        // Steal words from base language
        for (int i = 0; i < outputSize; i++) {
            Word *word = (*lang)->stealLastWord();
            subsetWords.push_back(word);
        }

        // Create new language with collected words but based on original
        // language i.e. having the same states and alphabet.
        Language *L = new Language(subsetWords, (*lang));
        subset->push_back(L);

        // Release stolen words
        for (auto st = subsetWords.begin(); st != subsetWords.end(); ++st) {
            delete (*st);
        }
    }


    return subset;
}