//
// Created by dybisz on 11/12/15.
//

#ifndef AC_GLOBAL_SETTINGS_H
#define AC_GLOBAL_SETTINGS_H

#include <string>
#include <cmath>
#include <iostream>

// Few remarks about whole project:
// |--o   symbols take values from interval [1; _numberOfSymbols]
// |--o   states are marked by values from interval [1; _numberOfStates]
// |--o   actual values declared in global_settings.cpp (<3 c++)
// |--o   alphabet is represented by integers from interval [_alphabet[0], _alphabet.size()]

namespace global_settings {
    /* ------ EXPERIMENT SETTINGS ----- */
    // ID of experiment to run
    // 0: Main optimizer
    // 1: DFA Generation
    extern int EXPERIMENT_ID;

    /* ------ CLASSIFICATION SETTINGS ----- */
    // Path to xls file with native objects
    extern std::string NATIVE_XLS_PATH;
    // Path to xls file with foreign objects
    extern std::string FOREIGN_XLS_PATH;
    // How many states corresponds to native languages
    extern int STATES_PER_NATIVE;
    // How many states corresponds to foreign languages
    extern int STATES_PER_FOREIGN;
    // The alphabet size defines the precision of transformation
    extern int ALPHABET_SIZE;
    // The ratio of testing set as opposed to full native set.
    // If Full Set = 100 and ratio = 0.3
    // then Testing Set = 30.
    extern double TESTING_SET_RATIO;
    // How many of provided classes should be loaded to Hill Climber based
    // experiment.
    extern int NUMBER_OF_CLASSES;
    // How many of provided patterns per class should be loaded to
    // Hill Climber based experiment
    extern int PATTERNS_PER_CLASS;

    // Maximum iterations of PSO algorithm
    extern int MAX_ITER;
    // TODO comment
    extern double LEARNING_FACTOR;
    // TODO comment
    extern double PARTICLE_VEL_WEIGHT;

    // When encoding particle back to automaton
    // each dimension must be casted down to integer value.
    // If p[i] > x.5 then take the ceiling.
    // otherwise take the floor.
    // Formally:
    //      encodedValue = (int)p[i]
    //      delta = p[i] - encodedValue
    //      if delta > ENCODING_DELTA
    //          encodedValue++
    //
    extern double ENCODING_DELTA;

    // Becouse of the nature of the encoding the
    // upper interval bound must a bit less than:
    // n + ENCODING_DELTA
    extern double UPPER_BOUND_ERR;

    // The maximum change that particle can make in single iteration
    extern double MAX_VELOCITY;

    extern int SWARM_SIZE;

    /* ------ THREAD SETTINGS ----- */

    // If the optimal number of threads can not be determined by the system
    // this value will be used
    extern int DEFAULT_THREAD_COUNT;

    // The actual number of threads to be used in computation.
    // If the value is below 1, then it will be up to the system to choose
    // the optimal number of threads.
    // If the optimal number of threads can not be determined, then
    // DEFAULT_THREAD_COUNT will be used.
    extern int TRUE_THREAD_COUNT;

    /* ------ CLUSTERING ----- */
    // The convergence tolerance in kmeans
    extern double KM_TOL;
    // The maximum iterations of kmeans
    extern int KM_MAX_ITER;

    // Starting number of cluster to evaluate.
    extern int START_K;
    // Finishing number of cluster to evaluate.
    extern int END_K;

    /* ------ LOGGER ----- */
    // Main directory of logs
    extern std::string LOG_MAIN_DIR;

    // Directory of current computation instance
    extern std::string LOG_CURR_DIR;

//------------------------------------------------------------------------------

    void setFlags();

    /*
     * Prints all the settings.
     * TODO Do it automatically.
     */
    void printPSOSettings();
}


#endif //AC_GLOBAL_SETTINGS_H
