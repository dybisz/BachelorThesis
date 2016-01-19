//
// Created by jakub on 1/19/16.
//

#include <classifier_constructor/settings/pso_settings.h>

#include <logger/logger_settings.h>
#include <sstream>
#include <logger/log.h>
#include <console/flag_reader.h>
#include <cmath>
#include <classifier_constructor/settings/settings.h>

using namespace console;


namespace settings {
    int MAX_ITER                = 99;
    double LEARNING_FACTOR      = 0.5 + log(2.0);
    double PARTICLE_VEL_WEIGHT  = 1.0 / (2.0 * log(2.0));
    double ENCODING_DELTA       = 0.5f;
    double UPPER_BOUND_ERR      = 0.001f;
    double MAX_VELOCITY         = 0.3f;
    int SWARM_SIZE              = 100;


//------------------------------------------------------------------------------

    void setPSOFlags(){
        /* ------ PSO SETTINGS ----- */
        addFlag(Flag("I", "max-iter",
                     "Maximum iterations of classifier",
                     INT, &settings::MAX_ITER));

        addFlag(Flag("v", "vel-weight",
                     "Particle Velocity Weight",
                     DOUBLE,
                     &settings::PARTICLE_VEL_WEIGHT));

        addFlag(Flag("V", "max-vel",
                     "Max Velocity",
                     DOUBLE,
                     &settings::MAX_VELOCITY));

        addFlag(Flag("S", "swarm-size",
                     "Swarm size",
                     INT,
                     &settings::SWARM_SIZE));

    }

    /*
     * Prints all the settings.
     */
    void printPSOSettings(){
        const std::string PATH_TO_VALUE = ".";
        int startColumn = 50;

        std::stringstream ss;
        std::string s = "";

        ss << "PSO SETTINGS" <<std::endl <<std::endl;

        s = "MAX_ITER ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_ITER << std::endl;

        s = "PARTICLE_VEL_WEIGHT ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << PARTICLE_VEL_WEIGHT << std::endl;

        s = "MAX_VELOCITY ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_VELOCITY << std::endl;

        s = "SWARM_SIZE";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << SWARM_SIZE << std::endl;

        logger::log(File(LOGS_SETTINGS_FILE_NAME), ss.str());
    }
}
