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
 * |
 * |-o [FN] - (False Negative)  - the number of elements of the considered class,
 * |                              incorrectly classified to other classes.
 * |
 * |-o [FP] - (False Positive)  - the number of elements of other classes,
 * |                              incorrectly classified to the considered class.
 * |
 * |-o [TN] - (True Negative)   - the number of elements of other classes,
 * |                              correctly classified to other classes.
 * |
 * |-o [ACCURACY]               - ([TP] + [TN]) / ([TP] + [TN] + [FP] + [FM])
 * |
 * |-o [SENSITIVITY]            - [TP] / ([TP] + [FN])
 * |
 * |-o [PRECISION]              - [TP] / ([TP] + [FP])
 * |
 * |-o [F-MEASURE]              - 2 * ([PRECISION] * [SENSITIVITY])
 *                                              / ([PRECISION] + [SENSITIVITY])
 *
 * Additional naming description:
 * |-o [Distinct]               - treats provided set of languages as distinct
 * |                              one. It means that a word will be treated as
 * |                              e.g TP iff its computation ends in a state
 * |                              specified by its corresponding language.
 * |
 * |-o [Overall]                - sees provided set of languages as a one i.e
 *                                it only checks if each word does end its
 *                                computations in any of states related to
 *                                the provided set. E.g. for native languages
 *                                it will tell how many native symbols were
 *                                classified as a symbol.
 */
namespace quality {

    /* ----------------------- */
    /* -----MAIN METHODS ----- */
    /* ----------------------- */

    // Computes TP/FN/FP/TN among provided native and foreign languages,
    // Computations are based on specified DFA. Normally, the dfa should be
    // the best result from previously run PSO.
    //
    // REMARK:  As for naming, please refer to the header comment.
    int numberOfTPDistinct(vector<Language *> *nativeLanguages,
                           DFA *dfa);

    int numberOfTPOverall(vector<Language *> *nativeLanguages,
                          DFA *dfa);

    int numberOfFNDistinct(vector<Language *> *nativeLanguages,
                           DFA *dfa);

    int numberOfFNOverall(vector<Language *> *nativeLanguages,
                          DFA *dfa);

    // Because one may not be interested in actual TP/FN/FP/TN percentage -
    // we provide methods to compute ratio between all considered words and
    // TP/FN/FP/TN ones. As previous, 2 version of each counting method has
    // been supplied.
    //
    // REMARK:  As for naming, please refer to header comment.
    double percentageTPDistinct(vector<Language *> *nativeLanguages,
                                DFA *dfa);

    double percentageTPOverall(vector<Language *> *nativeLanguages,
                               DFA *dfa);

    double percentageFNDistinct(vector<Language *> *nativeLanguages,
                                DFA *dfa);

    double percentageFNOverall(vector<Language *> *nativeLanguages,
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
    // with counter.
    int _countNumberOfWords(vector<Language *> *languages);

    // Gather all states corresponding to provided languages. Method created
    // mainly for [Overall]-type calculations.
    vector<State *> _collectStates(vector<Language *> *pLanguages);

    // Returns pointers to words classified as TP/FN/FP/TN. As usual it comes
    // in two versions explained in the header comment. We treat  them as an
    // auxiliary methods to keep main ones as transparent as possible.

    // WARNING: returned pointers should not be freed. They are
    //          released by corresponding languages classes.
    vector<Word *> *_gatherTPDistinct(vector<Language *> *nativeLanguages,
                                      DFA *dfa);

    vector<Word *> *_gatherTPOverall(vector<Language *> *nativeLanguages,
                                     DFA *dfa);

    vector<Word *> *_gatherFNDistinct(vector<Language *> *nativeLanguages,
                                      DFA *dfa);

    vector<Word *> *_gatherFNOverall(vector<Language *> *nativeLanguages,
                                     DFA *dfa);

    // Method checks for which words from pLanguage, their computation ends in
    // states from pCorrectStates and saves pointers to those words in pStorage.
    // pDFA constitutes a method of computation.
    void _getTrueOnesFrom(Language *pLanguage, DFA *pDFA,
                          vector<State *> *pCorrectStates,
                          vector<Word *> *pStorage);

    // method checks for which words from pLanguage, their computation ends in
    // different states than those provided in pCorrectStates and saves pointers
    // to such a words in pStorage. pDFA is used to perform computations.
    void _getFalseOnesFrom(Language *pLanguage, DFA *pDFA,
                           vector<State *> *pCorrectStates,
                           vector<Word *> *pStorage);

}

#endif //BACHELOR_THESIS_QUALITY_H
