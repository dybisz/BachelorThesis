//
// Created by jakub on 1/19/16.
//

#include "classifier_constructor/settings/log_settings.h"

#include <string>
#include <console/flag_reader.h>
#include <sstream>
#include <logger/logger_settings.h>
#include <logger/log.h>
#include <classifier_constructor/settings/settings.h>

using namespace console;

namespace settings {
    // Main directory of logs
    std::string LOG_MAIN_DIR            = "logs";

    // Directory of current computation instance
    std::string LOG_CURR_DIR            = "TEST";

    std::string LOGS_SETTINGS_FILE_NAME = "settings.txt";

    void setLogFlags(){
        /* ------ LOGGER ----- */

        addFlag(Flag("D", "log-main-dir",
                     "Main directory to store all logs",
                     STRING,
                     &settings::LOG_MAIN_DIR));
        addFlag(Flag("d", "log-dir",
                     "directory to store logs of current computations",
                     STRING,
                     &settings::LOG_CURR_DIR));
    }

    /*
     * Prints all the settings.
     */
    void printLogSettings(){
        const std::string PATH_TO_VALUE = ".";
        int startColumn = 50;

        std::stringstream ss;
        std::string s = "";

        ss  << "LOG SETTINGS" <<std::endl <<std::endl;

        s = "LOG_MAIN_DIR ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << LOG_MAIN_DIR << std::endl;

        s = "LOG_CURR_DIR ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << LOG_CURR_DIR << std::endl;

        s = "LOGS_SETTINGS_FILE_NAME ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << LOGS_SETTINGS_FILE_NAME << std::endl;

        logger::log(File(LOGS_SETTINGS_FILE_NAME), ss.str());
    }
}
