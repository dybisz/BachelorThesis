//
// Created by jakub on 1/19/16.
//

#ifndef BACHELOR_THESIS_LOG_SETTINGS_H
#define BACHELOR_THESIS_LOG_SETTINGS_H

#include <string>

namespace settings {
    // Main directory of logs
    extern std::string LOG_MAIN_DIR;

    // Directory of current computation instance
    extern std::string LOG_CURR_DIR;

    extern std::string LOGS_SETTINGS_FILE_NAME;


    void setLogFlags();

    /*
     * Prints all the settings.
     */
    void printLogSettings();
}

#endif //BACHELOR_THESIS_LOG_SETTINGS_H
