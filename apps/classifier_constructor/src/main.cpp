#ifndef AC_MAIN_H
#define AC_MAIN_H

#include <classifier_constructor/experiments/classification_exp.h>

#include <math/random.h>

#include <logger/log.h>

#include <console/flag_reader.h>

#include <threading/thread_util.h>

#include <string>
#include <stdlib.h>
#include <classifier_constructor/settings/thread_settings.h>
#include <classifier_constructor/settings/pso_settings.h>
#include <classifier_constructor/settings/log_settings.h>
#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_constructor/settings/app_settings.h>
#include <classifier_constructor/settings/settings.h>
#include <classifier_constructor/experiments/transformation_exp.h>

using namespace std;

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//

/*
 * Initialises the application resources
 */
void initApp(int argc, char *argv[]);

/*
 * Initiates all flags from settings
 */
void initFlags(int argc, char *argv[]);

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
        case 0:
            experiments::runClassification();
            break;
        case 1:
            experiments::runTransformationAnalysis();
            break;
        default:
            std::string what = "Experiment ID: " +
                               to_string(settings::EXPERIMENT_ID) +
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
    // Start the seed
    rnd::seed();

    // Set the number of threads to be activated
    setTrueNumberOfThreads();

    initFlags(argc, argv);

    // Initiates the logging functionality
    logger::settings::LOG_MAIN_DIR = settings::LOG_MAIN_DIR;
    logger::settings::LOG_CURR_DIR = settings::LOG_CURR_DIR;
    logger::initLog();

    settings::printAllSettings();
}

void initFlags(int argc, char *argv[]){
    console::clearFlags();

    settings::setAllFlags();

    console::readFlags(argc, argv);
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


#endif //AC_MAIN