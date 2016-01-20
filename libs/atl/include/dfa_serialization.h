//
// Created by jakub on 12/4/15.
//

#ifndef AC_DFA_LOADER_H
#define AC_DFA_LOADER_H

#include <automata/dfa.h>

/*
 * This module is responsible for loading DFA from file.
 * The file should be in Unified Form:
 *      4,2,2,4,3,3,3,3,4,4
 * where:
 *      - First number is number of states, 4
 *      - Second number is number of symbols, 2
 *      - Next entries are consecutive rows of transition table Q x E -> Q
 *      - Thus the example from above should look like the following:
 *          | a | b |
 *          |___|___|
 *       q1 | 2 | 4 |
 *       q2 | 3 | 3 |
 *       q3 | 3 | 3 |
 *       q4 | 4 | 4 |
 *  Warning: The states and symbols start indexing from '1'
 */

namespace dfa_serialization
{
    const std::string DFA_EXTENSION = ".dfa";

    /*
     * Saves the DFA to string using the unified form
     */
    std::string saveDFAToString(const DFA& dfa);

    /*
     * Saves the DFA to file using the unified form
     */
    void saveDFAToFile(const DFA& dfa,
                       std::string filepath, std::string name);

    /*
     * Loads DFA from file
     */
    DFA* loadDFAFromFile(std::string filename);

    /*
     * Loads DFA from a string in Unified Form
     */
    DFA* loadDFAFromString(std::string dfaURL);
}

#endif //AC_DFA_LOADER_H
