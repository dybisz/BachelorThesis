//
// Created by jakub on 1/20/16.
//

#include "classifier_constructor/experiments/transformation_exp.h"

#include <transformation/transformation_analyzer.h>

#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_constructor/settings/transformation_settings.h>

#include <logger/log.h>
#include <xls_loader.h>

using namespace transformation;

namespace experiments {

    void runTransformationAnalysis(){
        logger::log("Starting Transformation Analysis");

        logger::log("Loading Patterns");
        XlsLoader nativeXLSLoader(settings::NATIVE_XLS_PATH);
        XlsLoader foreignXLSLoader(settings::FOREIGN_XLS_PATH);

        std::vector<Class *> *nativePatterns = nativeXLSLoader.getClasses();
        std::vector<Class *> *foreignPatterns = foreignXLSLoader.getClasses();

        logger::log("Starting Transformation Analysis");

        TransformationAnalyzer transformationAnalyzer
                (
                        nativePatterns,
                        settings::MIN_ALHPABET_SIZE,
                        settings::MAX_ALHPABET_SIZE
                );

        transformationAnalyzer.runAnalysis();

        logger::log("Printing Results");

        transformationAnalyzer.printResults();
    }
}