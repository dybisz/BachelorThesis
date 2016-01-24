//
// Created by dybisz on 20.12.15.
//

#include <gtest/gtest.h>
#include "class.h"
#include "transformation/transformation.h"
#include <xls_loader.h>

using namespace std;
using namespace transformation;

string DATA_PATH2 = "./res/fv_example.xls";

TEST(PatternsToLanguages, Pattern_Init) {
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH2);
    vector<Language *> * languages = transform(xlsLoader->getClasses(), 2, 5);
    delete xlsLoader;
    delete languages;
}

TEST(PatternsToLanguages, Pattern_Wrong_Input) {
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH2);
    vector<Language *> * languages = NULL;
    ASSERT_ANY_THROW(languages = transform(xlsLoader->getClasses(), -1, -1));
    if(languages != NULL) delete languages;
    delete xlsLoader;
}