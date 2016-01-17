//
// Created by dybisz on 11/12/15.
//

#include <sstream>
#include <logger/log.h>
#include "settings/global_settings.h"
#include <console/flag.h>
#include <console/flag_reader.h>

using namespace console;

// Meaning of constants described in global_settings.h
// This file is just for quick values manipulations
namespace global_settings {
    /* ------ EXPERIMENT SETTINGS ----- */
    int EXPERIMENT_ID           = 0;

    /* ------ CLASSIFICATION SETTINGS ----- */
    std::string NATIVE_XLS_PATH     = "";
    std::string FOREIGN_XLS_PATH    = "";

    int STATES_PER_NATIVE           = 1;
    int STATES_PER_FOREIGN          = 1;
    int ALPHABET_SIZE               = 4;
    double TESTING_SET_RATIO        = 0.4;
    int NUMBER_OF_CLASSES           = 4;
    int PATTERNS_PER_CLASS          = 150;

    int MAX_ITER                = 99;
    double LEARNING_FACTOR      = 0.5 + log(2.0);
    double PARTICLE_VEL_WEIGHT  = 1.0 / (2.0 * log(2.0));
    double ENCODING_DELTA       = 0.5f;
    double UPPER_BOUND_ERR      = 0.001f;
    double MAX_VELOCITY         = 0.3f;
    int SWARM_SIZE              = 100;

    /* ------ THREAD SETTINGS ----- */
    int DEFAULT_THREAD_COUNT    = 4;
    int TRUE_THREAD_COUNT       = 0;

    /* ------ CLUSTERING ----- */
    double KM_TOL               = 0.0001f;
    int KM_MAX_ITER             = 1000;
    int START_K                 = 2;
    int END_K                   = 6;

    /* ------ LOGGER ----- */
    std::string LOG_MAIN_DIR    = "./logs";
    std::string LOG_CURR_DIR    = "TEST";

    //--------------------------------------------------------------------------

    void setFlags(){
        addFlag(Flag("E", "exp",
                             "Expiriment ID - "
                                     "0: PSO Optimizer",
                             INT, &global_settings::EXPERIMENT_ID));

        /* ------ CLASSIFICATION SETTINGS ----- */
        addFlag(Flag("N", "cl-native-path",
                             "Path to xls file with Native objects",
                             STRING, &global_settings::NATIVE_XLS_PATH));

        addFlag(Flag("F", "cl-foreign-path",
                             "Path to xls file with Foreign objects",
                             STRING, &global_settings::FOREIGN_XLS_PATH));

        addFlag(Flag("C", "cl-states-native",
                             "Number of states corresponding to native "
                                     "languages",
                             INT, &global_settings::STATES_PER_NATIVE));

        addFlag(Flag("c", "cl-states-foreign",
                             "Number of states corresponding to foreign "
                                     "languages",
                             INT, &global_settings::STATES_PER_FOREIGN));

        addFlag(Flag("A", "cl-alph-size",
                             "Size of the alphabet - defines precision",
                             INT, &global_settings::ALPHABET_SIZE));

        addFlag(Flag("T", "cl-test-ratio",
                             "Ratio of Test set",
                             DOUBLE, &global_settings::TESTING_SET_RATIO));

        /* ------ PSO SETTINGS ----- */
        addFlag(Flag("I", "max-iter",
                             "Maximum iterations of classifier",
                             INT, &global_settings::MAX_ITER));

        addFlag(Flag("v", "vel-weight",
                             "Particle Velocity Weight",
                             DOUBLE,
                             &global_settings::PARTICLE_VEL_WEIGHT));

        addFlag(Flag("V", "max-vel",
                             "Max Velocity",
                             DOUBLE,
                             &global_settings::MAX_VELOCITY));

        addFlag(Flag("S", "swarm-size",
                             "Swarm size",
                             INT,
                             &global_settings::SWARM_SIZE));

        /* ------ THREADING ----- */

        addFlag(Flag("g", "d-thread-count",
                             "Default Thread Count - used only when system"
                                     " can't determine optimal number of "
                                     "threads",
                             INT,
                             &global_settings::DEFAULT_THREAD_COUNT));

        addFlag(Flag("G", "t-thread-count",
                             "True Thread Count - How many threads should be "
                                     "activated. If value is below 1 then "
                                     "Optimal number of threads will be chosen",
                             INT,
                             &global_settings::TRUE_THREAD_COUNT));


        /* ------ CLUSTERING ----- */

        addFlag(Flag("m", "km-tol",
                             "K-means convergance tolerance",
                             DOUBLE,
                             &global_settings::KM_TOL));
        addFlag(Flag("i", "km-iter",
                             "K-means maxium iterations",
                             INT,
                             &global_settings::KM_MAX_ITER));

        addFlag(Flag("k", "km-s-k",
                             "Cluster evaluation starting k",
                             INT,
                             &global_settings::START_K));
        addFlag(Flag("K", "km-e-k",
                             "Cluster evaluation ending k",
                             INT,
                             &global_settings::END_K));

        /* ------ LOGGER ----- */

        addFlag(Flag("D", "log-main-dir",
                             "Main directory to store all logs",
                             STRING,
                             &global_settings::LOG_MAIN_DIR));
        addFlag(Flag("d", "log-dir",
                             "directory to store logs of current computations",
                             STRING,
                             &global_settings::LOG_CURR_DIR));

    }

    void printPSOSettings(){
        const std::string PATH_TO_VALUE = ".";
        int startColumn = 50;

        std::stringstream ss;
        std::string s = "";

        ss << std::endl<< "SETTINGS" <<std::endl;

        ss << std::endl<< "EXPERIMENT SETTINGS" <<std::endl <<std::endl;

        s = "EXPERIMENT_ID ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << EXPERIMENT_ID << std::endl;


        ss << std::endl<< "CLASSIFICATION SETTINGS" <<std::endl <<std::endl;

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

        s = "ENCODING_DELTA ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << ENCODING_DELTA << std::endl;

        s = "UPPER_BOUND_ERR ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << UPPER_BOUND_ERR << std::endl;

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

        ss << std::endl << "THREADS SETTINGS" <<std::endl << std::endl;

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

        ss << std::endl<< "CLUSTERING SETTINGS" <<std::endl <<std::endl;

        s = "KM_TOL ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << KM_TOL << std::endl;

        s = "KM_MAX_ITER ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << KM_MAX_ITER << std::endl;

        s = "START_K ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << START_K << std::endl;

        s = "END_K ";
        ss << s;
        for(unsigned int i = 0;i < startColumn-s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << END_K << std::endl;

        ss << std::endl<< "LOGGER SETTINGS" <<std::endl <<std::endl;;

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


        logger::log(File("settings.txt"), ss.str());
    }
}
