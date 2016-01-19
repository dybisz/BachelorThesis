//
// Created by jakub on 1/19/16.
//

#ifndef BACHELOR_THESIS_CLASSIFIER_SETTINGS_H
#define BACHELOR_THESIS_CLASSIFIER_SETTINGS_H

#include <string>

namespace settings {

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
    // How many of provided classes should be loaded to
    extern int NUMBER_OF_CLASSES;
    // How many of provided patterns per class should be loaded
    extern int PATTERNS_PER_CLASS;


    void setClassifierFlags();

    /*
     * Prints all the settings.
     * TODO Do it automatically.
     */
    void printClassifierSettings();
}

#endif //BACHELOR_THESIS_CLASSIFIER_SETTINGS_H
