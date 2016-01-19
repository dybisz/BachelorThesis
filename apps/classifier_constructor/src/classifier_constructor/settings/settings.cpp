//
// Created by jakub on 1/19/16.
//

#include <classifier_constructor/settings/app_settings.h>
#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_constructor/settings/pso_settings.h>
#include <classifier_constructor/settings/log_settings.h>
#include <classifier_constructor/settings/thread_settings.h>
#include "classifier_constructor/settings/settings.h"

namespace settings{
    void setAllFlags(){
        settings::setAppFlags();
        settings::setClassifierFlags();
        settings::setLogFlags();
        settings::setPSOFlags();
        settings::setThreadFlags();
    }

    void printAllSettings(){
        printAppSettings();
        printClassifierSettings();
        printLogSettings();
        printPSOSettings();
        printThreadSettings();
    }
}