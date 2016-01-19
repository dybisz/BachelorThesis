//
// Created by jakub on 1/19/16.
//

#ifndef BACHELOR_THESIS_THREAD_SETTINGS_H
#define BACHELOR_THESIS_THREAD_SETTINGS_H

namespace settings {

    // If the optimal number of threads can not be determined by the system
    // this value will be used
    extern int DEFAULT_THREAD_COUNT;

    // The actual number of threads to be used in computation.
    // If the value is below 1, then it will be up to the system to choose
    // the optimal number of threads.
    // If the optimal number of threads can not be determined, then
    // DEFAULT_THREAD_COUNT will be used.
    extern int TRUE_THREAD_COUNT;

    void setThreadFlags();

    /*
     * Prints all the settings.
     */
    void printThreadSettings();
}

#endif //BACHELOR_THESIS_THREAD_SETTINGS_H
