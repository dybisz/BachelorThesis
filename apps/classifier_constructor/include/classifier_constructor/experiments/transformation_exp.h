//
// Created by jakub on 1/20/16.
//

#ifndef BACHELOR_THESIS_TRANSFORMATION_EXP_H
#define BACHELOR_THESIS_TRANSFORMATION_EXP_H

#include <class.h>

namespace experiments {
    void runTransformationAnalysis();

    void runTransformationNativeVersusForeign();

    Class combineClasses(vector<Class*>* classes, int label);
}

#endif //BACHELOR_THESIS_TRANSFORMATION_EXP_H
