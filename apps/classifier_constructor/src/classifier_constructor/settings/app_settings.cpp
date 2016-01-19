//
// Created by jakub on 1/19/16.
//

#include <console/flag_reader.h>
#include <iostream>
#include <sstream>
#include <logger/logger_settings.h>
#include <logger/log.h>
#include <classifier_constructor/settings/settings.h>
#include "classifier_constructor/settings/app_settings.h"

using namespace console;

namespace settings {

    int EXPERIMENT_ID = 0;

    void setAppFlags(){
        addFlag(Flag("E", "exp",
                     "Expiriment ID - "
                             "0: PSO Optimizer",
                     INT, &settings::EXPERIMENT_ID));
    }

    void printAppSettings(){
        const std::string PATH_TO_VALUE = ".";
        int startColumn = 50;

        std::stringstream ss;
        std::string s = "";

        ss << "APP SETTINGS" <<std::endl <<std::endl;

        s = "EXPERIMENT_ID ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << EXPERIMENT_ID << std::endl;

        logger::log(File(LOGS_SETTINGS_FILE_NAME), ss.str());
    }
}