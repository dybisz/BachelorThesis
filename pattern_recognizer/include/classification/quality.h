//
// Created by dybisz on 23.12.15.
//

#ifndef BACHELOR_THESIS_QUALITY_H
#define BACHELOR_THESIS_QUALITY_H

#include <vector>
#include <string>
#include <language.h>
#include <dfa.h>

using namespace std;

/*
 * Namespace is in charge of measuring (in fact 8) different values:
 * |
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
 * |-o [ACCURACY]               - ([TP] + [TN]) / ([TP] + [TN] + [FP] + [FN])
 * |
 * |-o [SENSITIVITY]            - [TP] / ([TP] + [FN])
 * |
 * |-o [PRECISION]              - [TP] / ([TP] + [FP])
 * |
 * |-o [F-MEASURE]              - 2 * ([PRECISION] * [SENSITIVITY])
 *                                              / ([PRECISION] + [SENSITIVITY])
 *
 * Additional naming description:
 * |
 * |-o [Distinct]               - treats provided set of languages as distinct
 * |                              one. It means that a word will be treated as
 * |                              e.g TP iff its computation ends in a state
 * |                              specified by its corresponding language.
 * |                              in other words it checks if symbol was
 * |                              classified as a correct one, rather than
 * |                              as a symbol at all.
 * |
 * |-o [Overall]                - sees provided set of languages as a one i.e
 *                                it only checks if each word does end its
 *                                computations in any of states related to
 *                                the provided set. E.g. for native languages
 *                                it will tell how many native symbols were
 *                                classified as a symbol.
 *
 * Methods of acquiring TP/FN/FP/TN:
 * |
 * |-o True Positive            - methods with [True] + native languages set
 * |
 * |-o False Negative           - methods with [False] + native languages set
 * |
 * |-o False Positive           - methods with [False] + foreign languages set
 * |
 * |-o True Negative            - methods with [True] + foreign languages set
 */
namespace quality {

    /* ----------------------- */
    /* -----MAIN METHODS ----- */
    /* ----------------------- */

    // Methods used to generate summary of TP/FN/FP/TN and
    // Accuracy/Sensitivity/Precision/F-Measure results for provided native
    // and foreign sets of languages. If one cares only for putting results
    // to some kind of log file or print them out this method is perfectly
    // suited. Output strings are conveniently formatted.
    string distinctResultsToString(vector<Language *> *nativeLanguages,
                                   vector<Language *> *foreignLanguages,
                                   DFA *dfa);

    string overallResultsToString(vector<Language *> *nativeLanguages,
                                  vector<Language *> *foreignLanguages,
                                  DFA *dfa);

    // Methods compute Accuracy/Sensitivity/Precision/F-Measure values.
    // Distinct and Overall methods has been provided for further, more precise
    // analysis of the results.
    //
    // REMARK: For naming explanation, please refer to the header comment.
    double calculateAccuracyDistinct(vector<Language *> *nativeLanguages,
                                     vector<Language *> *foreignLanguages,
                                     DFA *dfa);

    double calculateAccuracyOverall(vector<Language *> *nativeLanguages,
                                    vector<Language *> *foreignLanguages,
                                    DFA *dfa);

    double calculateSensitivityDistinct(vector<Language *> *nativeLanguages,
                                        vector<Language *> *foreignLanguages,
                                        DFA *dfa);

    double calculateSensitivityOverall(vector<Language *> *nativeLanguages,
                                       vector<Language *> *foreignLanguages,
                                       DFA *dfa);

    double calculatePrecisionDistinct(vector<Language *> *nativeLanguages,
                                      vector<Language *> *foreignLanguages,
                                      DFA *dfa);

    double calculatePrecisionOverall(vector<Language *> *nativeLanguages,
                                     vector<Language *> *foreignLanguages,
                                     DFA *dfa);

    double calculateFMeasureDistinct(vector<Language *> *nativeLanguages,
                                     vector<Language *> *foreignLanguages,
                                     DFA *dfa);

    double calculateFMeasureOverall(vector<Language *> *nativeLanguages,
                                    vector<Language *> *foreignLanguages,
                                    DFA *dfa);

    // Computes number of TP/FN/FP/TN among provided languages,
    // Computations are based on specified DFA. Normally, the dfa should be
    // the best result from previously run PSO.
    //
    // REMARK: For combination with native/foreign sets and naming convention,
    //         please refer to the [Methods of acquiring TP/FN/FP/TN] section
    //         of the header comment.
    int numberOfTrueDistinct(vector<Language *> *pLanguages,
                             DFA *dfa);

    int numberOfTrueOverall(vector<Language *> *pLanguages,
                            DFA *dfa);

    int numberOfFalseDistinct(vector<Language *> *pLanguages,
                              DFA *dfa);

    int numberOfFalseOverall(vector<Language *> *pLanguages,
                             DFA *dfa);

    // Because one may not be interested in actual TP/FN/FP/TN percentage -
    // we provide methods to compute ratio between all considered words and
    // TP/FN/FP/TN ones. As previous, 2 version of each counting method has
    // been supplied.
    //
    // REMARK: For combination with native/foreign sets and naming convention,
    //         please refer to the [Methods of acquiring TP/FN/FP/TN] section
    //         of the header comment.
    double percentageTrueDistinct(vector<Language *> *pLanguages,
                                  DFA *dfa);

    double percentageTrueOverall(vector<Language *> *pLanguages,
                                 DFA *dfa);

    double percentageFalseDistinct(vector<Language *> *pLanguages,
                                   DFA *dfa);

    double percentageFalseOverall(vector<Language *> *pLanguages,
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
    bool _stateOnList(int state, const vector<State *> *pStates);

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
    // REMARK:  For combination with native/foreign sets and naming convention,
    //          please refer to the [Methods of acquiring TP/FN/FP/TN] section
    //          of the header comment.
    vector<Word *> *_gatherTrueDistinct(vector<Language *> *pLanguages,
                                        DFA *dfa);

    vector<Word *> *_gatherTrueOverall(vector<Language *> *pLanguages,
                                       DFA *dfa);

    vector<Word *> *_gatherFalseDistinct(vector<Language *> *pLanguages,
                                         DFA *dfa);

    vector<Word *> *_gatherFalseOverall(vector<Language *> *pLanguages,
                                        DFA *dfa);

    // Method checks for which words from pLanguage, their computation ends in
    // states from pCorrectStates and saves pointers to those words in pStorage.
    // pDFA constitutes a method of computation.
    void _getTrueOnesFrom(Language *pLanguage, DFA *pDFA,
                          const vector<State *> *pCorrectStates,
                          vector<Word *> *pStorage);

    // Method checks for which words from pLanguage, their computation ends in
    // different states than those provided in pCorrectStates and saves pointers
    // to such a words in pStorage. pDFA is used to perform computations.
    void _getFalseOnesFrom(Language *pLanguage, DFA *pDFA,
                           const vector<State *> *pCorrectStates,
                           vector<Word *> *pStorage);
}

#endif //BACHELOR_THESIS_QUALITY_H
