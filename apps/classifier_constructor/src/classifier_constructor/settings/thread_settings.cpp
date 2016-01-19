//
// Created by jakub on 1/19/16.
//

#include "classifier_constructor/settings/thread_settings.h"
#include <sstream>
#include <logger/log.h>
#include <console/flag.h>
#include <console/flag_reader.h>
#include <classifier_constructor/settings/settings.h>

using namespace console;


namespace settings {

    int DEFAULT_THREAD_COUNT    = 4;
    int TRUE_THREAD_COUNT       = 0;

    void setThreadFlags(){
        addFlag(Flag("g", "d-thread-count",
                     "Default Thread Count - used only when system"
                             " can't determine optimal number of "
                             "threads",
                     INT,
                     &settings::DEFAULT_THREAD_COUNT));

        addFlag(Flag("G", "t-thread-count",
                     "True Thread Count - How many threads should be "
                             "activated. If value is below 1 then "
                             "Optimal number of threads will be chosen",
                     INT,
                     &settings::TRUE_THREAD_COUNT));
    }

    /*
     * Prints all the settings.
     */
    void printThreadSettings(){
        const std::string PATH_TO_VALUE = ".";
        int startColumn = 50;

        std::stringstream ss;
        std::string s = "";

        ss << "THREADS SETTINGS" <<std::endl <<std::endl;

        s = "DEFAULT_THREAD_COUNT ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << DEFAULT_THREAD_COUNT << std::endl;

        s = "TRUE_THREAD_COUNT ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << TRUE_THREAD_COUNT << std::endl;

        logger::log(File(LOGS_SETTINGS_FILE_NAME), ss.str());

    }
}
