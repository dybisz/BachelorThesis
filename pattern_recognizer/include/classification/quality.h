//
// Created by dybisz on 23.12.15.
//

#ifndef BACHELOR_THESIS_QUALITY_H
#define BACHELOR_THESIS_QUALITY_H

#include <vector>
#include <language.h>
#include <dfa.h>

using namespace std;

/*
 * Namespace is in charge of measuring (in fact 8) different values:
 * |-o [TP] - (True Positive)   - the number of elements of the considered class,
 * |                              correctly classified to this class.
 * |-o [FN] - (False Negative)  - the number of elements of the considered class,
 * |                              incorrectly classified to other classes.
 * |-o [FP] - (False Positive)  - the number of elements of other classes,
 * |                              incorrectly classified to the considered class.
 * |-o [TN] - (True Negative)   - the number of elements of other classes,
 * |                              correctly classified to other classes.
 * |-o [ACCURACY]               - ([TP] + [TN]) / ([TP] + [TN] + [FP] + [FM])
 * |-o [SENSITIVITY]            - [TP] / ([TP] + [FN])
 * |-o [PRECISION]              - [TP] / ([TP] + [FP])
 * |-o [F-MEASURE]              - 2 * ([PRECISION] * [SENSITIVITY])
 *                                              / ([PRECISION] + [SENSITIVITY])
 *
 * Additional naming description:
 * |-o [Distinct]               - treats foreign languages as distinct ones. It
 * |                              means that a foreign word will we treated as
 * |                              TP iff its computation ends in a state specified
 * |                              by its language.
 * |-o [Overall]                - sees foreign languages as a one i.e it only
 *                                checks if each foreign words does not end its
 *                                computation in any of states assigned to
 *                                native languages.
 */
namespace quality {

    /* ----------------------- */
    /* -----MAIN METHODS ----- */
    /* ----------------------- */

    // Computes True Positives among provided native and foreign languages,
    // Computations are based on specified DFA.Normally, the dfa should be
    // the best result from previously run PSO.

    // WARNING: returned pointers to words should not be freed. They are
    //          released by corresponding languages classes.
    // REMARK:  As for naming, please refer to header comment.
    vector<Word *> *gatherTPDistinct(vector<Language *> *nativeLanguages,
                                     vector<Language *> *foreignLanguages,
                                     DFA *dfa);

    vector<Word *> *gatherTPOverall(vector<Language *> *nativeLanguages,
                                    vector<Language *> *foreignLanguages,
                                    DFA *dfa);

    // Because one may not be interested in actual words pointers, rather
    // in TP percentage - we provide methods to compute ratio between
    // all considered words and TP ones. As previous, 2 version of TP counting
    // has been supplied.
    // REMARK:  As for naming, please refer to header comment.
    double computeTPDistinct(vector<Language *> *nativeLanguages,
                             vector<Language *> *foreignLanguages,
                             DFA *dfa);

    double computeTPOverall(vector<Language *> *nativeLanguages,
                            vector<Language *> *foreignLanguages,
                            DFA *dfa);

    /* --------------------- */
    /* ----- AUXILIARY ----- */
    /* --------------------- */

    // Due to temporary implementation's indexing mismatching, method must be
    // provided. It decreases entry of all words from provided languages by 1.
    void _convertWords(vector<Language *> *pLanguages);

    // Temporary method for decreasing word's entries by 1 - implementation
    // dependent
    void _convertWord(Word *word);

    // Check whether given state is on the list of states. For now state to
    // check in form of the integer but later on it should be changed to object
    // of State class.
    bool _stateOnList(int state, vector<State *> *pStates);

    // Returns number of words in provided languages. Just a hidden loop
    // with counter. We treat it as an auxiliary method to keep main methods
    // as transparent as possible.
    int _countNumberOfWords(vector<Language *> *languages);

    // Returns number of words classified as True Positives. As usual it comes
    // in two versions.
    int _numberOfTPDistinct(vector<Language *> *nativeLanguages,
                           vector<Language *> *foreignLanguages,
                           DFA *dfa);

    int _numberOfTPOverall(vector<Language *> *nativeLanguages,
                          vector<Language *> *foreignLanguages,
                          DFA *dfa);

    // Method checks for which words from pLanguage, their computation ends in
    // states from pCorrectStates and save pointers to those words in pStorage.
    // pDFA constitutes a method of computation.
    void _getTPFrom(Language *pLanguage, DFA *pDFA,
                    vector<State *> *pCorrectStates,
                    vector<Word *> *pStorage);

}

#endif //BACHELOR_THESIS_QUALITY_H
