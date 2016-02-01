//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_TRANSFORMATION_EXP_H
#define BACHELOR_THESIS_TRANSFORMATION_EXP_H

#include <class.h>

/*
 * Provides functionality for Transformation Analysis
 */
namespace experiments {

    /*
     * All native languages are considered individually.
     */
    void runTransformationAnalysis();

    /*
     * All native languages are considered to be one big langauges.
     * The transformation analysis is then run against Native vs Foreign
     */
    void runTransformationAnalysisNativeVersusForeign();

    Class combineClasses(vector<Class*>* classes, int label);
}

#endif //BACHELOR_THESIS_TRANSFORMATION_EXP_H
