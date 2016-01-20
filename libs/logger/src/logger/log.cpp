//
// Created by jakub on 11/22/15.
//

#include "logger/log.h"
#include <error.h>

#include <sys/stat.h>
#include <ctime>

#include <clock.h>

namespace logger
{
    void initLog() {
        // Create main log dir
        if (mkdir(settings::LOG_MAIN_DIR.c_str(), 0777) < 0)
            if (errno !=EEXIST) ERR("mkdir");

        // Get time
        std::string timeStr = clk::currentFullDateString(
                settings::DATE_SEPARATOR,
                settings::BETWEEN_SEPARATOR,
                settings::TIME_SEPARATOR);

        settings::FULL_DIR_STR = settings::LOG_CURR_DIR
                                        + settings::BETWEEN_SEPARATOR
                                        + timeStr;
        settings::FULL_DIR_STR = settings::LOG_MAIN_DIR
                                        + "/" + settings::FULL_DIR_STR;

        if (mkdir(settings::FULL_DIR_STR.c_str(), 0777) < 0)
            if (errno !=EEXIST) ERR("mkdir");

        // Inform about creating file
        std::cout << "Created Log directory: "
            << settings::FULL_DIR_STR << std::endl;

        std::string defaultLogFile =
            engine::makeLogPath(settings::DEFAULT_FILE_NAME);

        settings::DEFAULT_FILE_STREAM.open(defaultLogFile.c_str());
    }

    void closeLog(){
        settings::DEFAULT_FILE_STREAM.close();
    }

    void makeDir(std::string dir){
        if (mkdir(dir.c_str(), 0777) < 0)
            if (errno !=EEXIST)
                ERR(dir.c_str());
    }


    std::string makePath(std::string dir, std::string appendToDir){
        std::string path;
        std::string PATH_SEPARATOR = "/";

        path += dir + PATH_SEPARATOR + appendToDir;
        return path;
    }

    std::string makePath(const std::vector<std::string>& toPath){
        std::string path;
        std::string PATH_SEPARATOR = "/";

        for(unsigned int i = 0; i < toPath.size(); i++){
            path += toPath[i] + PATH_SEPARATOR;
        }
        return path;
    }
}