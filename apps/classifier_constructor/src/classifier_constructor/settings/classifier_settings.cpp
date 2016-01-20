//
// Created by jakub on 1/19/16.
//

#include "classifier_constructor/settings/classifier_settings.h"

#include <console/flag_reader.h>
#include <iostream>
#include <sstream>
#include <logger/logger_settings.h>
#include <logger/log.h>
#include <classifier_constructor/settings/settings.h>

using namespace console;

namespace settings {
    std::string NATIVE_XLS_PATH     = "../../../resources/digits/Natives.xls";
    std::string FOREIGN_XLS_PATH    =
            "../../../resources/digits/Foreign_90ccl.xls";

    int STATES_PER_NATIVE           = 1;
    int STATES_PER_FOREIGN          = 1;
    int ALPHABET_SIZE               = 4;
    double TESTING_SET_RATIO        = 0.4;
    int NUMBER_OF_CLASSES           = 4;
    int PATTERNS_PER_CLASS          = 800;

    void setClassifierFlags(){
        addFlag(Flag("N", "cl-native-path",
                     "Path to xls file with Native objects",
                     STRING, &settings::NATIVE_XLS_PATH));

        addFlag(Flag("F", "cl-foreign-path",
                     "Path to xls file with Foreign objects",
                     STRING, &settings::FOREIGN_XLS_PATH));

        addFlag(Flag("C", "cl-states-native",
                     "Number of states corresponding to native "
                             "languages",
                     INT, &settings::STATES_PER_NATIVE));

        addFlag(Flag("c", "cl-states-foreign",
                     "Number of states corresponding to foreign "
                             "languages",
                     INT, &settings::STATES_PER_FOREIGN));

        addFlag(Flag("A", "cl-alph-size",
                     "Size of the alphabet - defines precision",
                     INT, &settings::ALPHABET_SIZE));

        addFlag(Flag("T", "cl-test-ratio",
                     "Ratio of Test set",
                     DOUBLE, &settings::TESTING_SET_RATIO));

        addFlag(Flag("U", "classes-to-load",
                     "Classes to load from xls file",
                     INT,
                     &settings::NUMBER_OF_CLASSES));

        addFlag(Flag("u", "patterns-per-class",
                     "Maximum number of patterns in each class",
                     INT,
                     &settings::PATTERNS_PER_CLASS));
    }

    /*
     * Prints all the settings.
     */
    void printClassifierSettings(){
        const std::string PATH_TO_VALUE = ".";
        int startColumn = 50;

        std::stringstream ss;
        std::string s = "";

        ss << "CLASSIFICATION SETTINGS" <<std::endl <<std::endl;

        s = "NATIVE_XLS_PATH ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << NATIVE_XLS_PATH << std::endl;

        s = "FOREIGN_XLS_PATH ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << FOREIGN_XLS_PATH << std::endl;

        s = "STATES_PER_NATIVE ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << STATES_PER_NATIVE << std::endl;

        s = "STATES_PER_FOREIGN ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << STATES_PER_FOREIGN << std::endl;

        s = "ALPHABET_SIZE ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << ALPHABET_SIZE << std::endl;

        s = "TESTING_SET_RATIO ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << TESTING_SET_RATIO << std::endl;

        s = "LOADED CLASSES ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << NUMBER_OF_CLASSES << std::endl;

        s = "PATTERNS PER CLASS ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << PATTERNS_PER_CLASS << std::endl;

        logger::log(File(LOGS_SETTINGS_FILE_NAME), ss.str());
    }
}
