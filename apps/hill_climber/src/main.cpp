#ifndef AC_MAIN_H
#define AC_MAIN_H

#include <experiments/classification_exp.h>
#include <settings/global_settings.h>

#include <math/random.h>

#include <logger/log.h>

#include <console/flag_reader.h>

#include <threading/thread_util.h>

using namespace std;

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

/*
 * Initialises the application resources
 */
void initApp(int argc, char *argv[]);

/*
 * Closes the application resources
 */
void closeApp();

void setTrueNumberOfThreads();

//------------------------------------------------------------------------------

int main(int argc, char *argv[]) {
    initApp(argc, argv);

    // Choose experiment
    switch (settings::EXPERIMENT_ID) {
        case 1:
            // Prints all settings to the console
            settings::printHillClimberSettings();
            experiments::runHillClimberBasedClassification();
            break;
        default:
            std::string what = "Experiment ID: " +
                               std::to_string(settings::EXPERIMENT_ID) +
                               " is not a proper Experiment ID";
            console::usage(argv[0], what.c_str());
    }

    closeApp();

    return EXIT_SUCCESS;
}

//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//

void initApp(int argc, char *argv[]) {
    settings::setFlags();

    // Start the seed
    rnd::seed();

    // Read flags must be first!!!!
    console::readFlags(argc, argv);

    // Set the number of threads to be activated
    setTrueNumberOfThreads();

    // Initiates the logging functionality
    logger::settings::LOG_MAIN_DIR = settings::LOG_MAIN_DIR;
    logger::settings::LOG_CURR_DIR = settings::LOG_CURR_DIR;
    logger::initLog();
}

void closeApp() {
    logger::closeLog();
}

void setTrueNumberOfThreads(){
    // If the user set value below 1, change it
    if(settings::TRUE_THREAD_COUNT < 1){
        settings::TRUE_THREAD_COUNT = threading::getNumberOfCores();
        // If the system could not determine, choose the default value
        if(settings::TRUE_THREAD_COUNT < 1){
            settings::TRUE_THREAD_COUNT =
                    settings::DEFAULT_THREAD_COUNT;
        }
    }
}

//------------------------------------------------------------------------------



//------------------------------------------------------------------------------

#endif //AC_STANDARD_TRANSITION_T_H