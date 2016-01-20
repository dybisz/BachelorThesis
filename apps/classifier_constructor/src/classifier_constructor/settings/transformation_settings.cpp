//
// Created by jakub on 1/20/16.
//

#include "classifier_constructor/settings/transformation_settings.h"

#include <console/flag_reader.h>
#include <sstream>
#include <logger/log.h>
#include <classifier_constructor/settings/settings.h>

using namespace console;

namespace settings {

    int MIN_ALHPABET_SIZE = 10;
    int MAX_ALHPABET_SIZE = 12;


    void setTrasformationFlags(){
        addFlag(Flag("r", "min-alph",
                     "Minimal Alphabet Size",
                     INT, &settings::MIN_ALHPABET_SIZE));
        addFlag(Flag("R", "max-alph",
                     "Maximum Alphabet Size",
                     INT, &settings::MAX_ALHPABET_SIZE));
    }

    void printTransformationSettings(){
        const std::string PATH_TO_VALUE = ".";
        int startColumn = 50;

        std::stringstream ss;
        std::string s = "";

        ss << "TRANSFORMATION SETTINGS" <<std::endl <<std::endl;

        s = "MIN_ALHPABET_SIZE ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MIN_ALHPABET_SIZE << std::endl;

        s = "MAX_ALHPABET_SIZE ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_ALHPABET_SIZE << std::endl;

        logger::log(File(LOGS_SETTINGS_FILE_NAME), ss.str());
    }
}