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
namespace settings {
    /* ------ EXPERIMENT SETTINGS ----- */
    int EXPERIMENT_ID = 0;

    /* ------ CLASSIFICATION SETTINGS ----- */
    std::string NATIVE_XLS_PATH = "";
    std::string FOREIGN_XLS_PATH = "";

    int STATES_PER_NATIVE = 1;
    int STATES_PER_FOREIGN = 1;
    int ALPHABET_SIZE = 4;
    double TESTING_SET_RATIO = 0.4;
    int HILL_CLIMBER_STATES = 50;
    int NUMBER_OF_CLASSES = 4;
    int PATTERNS_PER_CLASS = 150;

    int MAX_ITER = 99;
    double LEARNING_FACTOR = 0.5 + log(2.0);
    double PARTICLE_VEL_WEIGHT = 1.0 / (2.0 * log(2.0));
    double ENCODING_DELTA = 0.5f;
    double UPPER_BOUND_ERR = 0.001f;
    double SPEED_FACTOR = 0.05f;
    double MAX_VELOCITY = 0.3f;
    double POPULATION_FACTOR = 1.0f;
    double FITNESS_TOLERANCE = 1.0f;
    int SWARM_SIZE = 100;

    /* ------ THREAD SETTINGS ----- */
    int DEFAULT_THREAD_COUNT = 4;
    int TRUE_THREAD_COUNT = 0;

    /* ------ CLUSTERING ----- */
    double KM_TOL = 0.0001f;
    int KM_MAX_ITER = 1000;
    int START_K = 2;
    int END_K = 6;

    /* ------ LOGGER ----- */
    std::string LOG_MAIN_DIR = "./logs";
    std::string LOG_CURR_DIR = "TEST";
    //--------------------------------------------------------------------------

    void setFlags() {
        /* ------ EXPERIMENTS SETTINGS ----- */

        addFlag(Flag("E", "exp",
                             "Expiriment ID - "
                                     "0: PSO Optimizer, "
                                     "1: Hill Climber Optimizer,"
                                     "2: DFA Generation, "
                                     "3: Word Generation",
                             INT, &settings::EXPERIMENT_ID));

        /* ------ CLASSIFICATION SETTINGS ----- */
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




        /* ------ PSO SETTINGS ----- */
        addFlag(Flag("I", "max-iter",
                             "Maximum iterations of classifier",
                             INT, &settings::MAX_ITER));

        addFlag(Flag("l", "learn-fac",
                             "Learning Factor",
                             DOUBLE,
                             &settings::LEARNING_FACTOR));


        addFlag(Flag("v", "vel-weight",
                             "Particle Velocity Weight",
                             DOUBLE,
                             &settings::PARTICLE_VEL_WEIGHT));

        addFlag(Flag("s", "speed-fac",
                             "Speed Factor",
                             DOUBLE,
                             &settings::SPEED_FACTOR));

        addFlag(Flag("V", "max-vel",
                             "Max Velocity",
                             DOUBLE,
                             &settings::MAX_VELOCITY));

        addFlag(Flag("p", "pop-fac",
                             "Population Factor",
                             DOUBLE,
                             &settings::POPULATION_FACTOR));


        addFlag(Flag("f", "fit-tol",
                             "Fitness Tolerance",
                             DOUBLE,
                             &settings::FITNESS_TOLERANCE));

        addFlag(Flag("S", "swarm-size",
                             "Swarm size",
                             INT,
                             &settings::SWARM_SIZE));

        /* ----- HILL CLIMBER SETTINGS ----- */
        addFlag(Flag("H", "hill-climber-states",
                             "States in Hill Climber experiment",
                             INT,
                             &settings::HILL_CLIMBER_STATES));

        addFlag(Flag("U", "classes-to-load",
                             "States in Hill Climber experiment",
                             INT,
                             &settings::NUMBER_OF_CLASSES));

        addFlag(Flag("u", "patterns-per-class",
                             "States in Hill Climber experiment",
                             INT,
                             &settings::PATTERNS_PER_CLASS));

        /* ------ THREADING ----- */

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


        /* ------ CLUSTERING ----- */

        addFlag(Flag("m", "km-tol",
                             "K-means convergance tolerance",
                             DOUBLE,
                             &settings::KM_TOL));
        addFlag(Flag("i", "km-iter",
                             "K-means maxium iterations",
                             INT,
                             &settings::KM_MAX_ITER));

        addFlag(Flag("k", "km-s-k",
                             "Cluster evaluation starting k",
                             INT,
                             &settings::START_K));
        addFlag(Flag("K", "km-e-k",
                             "Cluster evaluation ending k",
                             INT,
                             &settings::END_K));

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

    void printHillClimberSettings() {
        const std::string PATH_TO_VALUE = ".";
        int startColumn = 50;

        std::stringstream ss;
        std::string s = "";

        ss << std::endl << "SETTINGS" << std::endl;

        s = "EXPERIMENT_ID ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << EXPERIMENT_ID << std::endl;

        s = "NATIVE_XLS_PATH ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << NATIVE_XLS_PATH << std::endl;

        s = "FOREIGN_XLS_PATH ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << FOREIGN_XLS_PATH << std::endl;

        s = "STATES ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << HILL_CLIMBER_STATES << std::endl;

        s = "ALPHABET_SIZE ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << ALPHABET_SIZE << std::endl;


        s = "MAX_ITER ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << MAX_ITER << std::endl;

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


        s = "LOG_MAIN_DIR ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << LOG_MAIN_DIR << std::endl;

        s = "LOG_CURR_DIR ";
        ss << s;
        for (unsigned int i = 0; i < startColumn - s.length(); i++)
            ss << PATH_TO_VALUE;
        ss << " ";
        ss << LOG_CURR_DIR;

        logger::log(File("settings.txt"), ss.str());
    }
}
