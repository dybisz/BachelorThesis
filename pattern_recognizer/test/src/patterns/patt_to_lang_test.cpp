//
// Created by dybisz on 20.12.15.
//

#include <gtest/gtest.h>
#include <pattern.h>
#include <patterns_to_languages.h>
#include <xls_loader.h>

using namespace std;
using namespace patterns_to_languages;

string DATA_PATH2 = "./src/xls/fv_example.xls";

TEST(PatternsToLanguages, Pattern_Init) {
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH2);
    vector<Language *> * languages = convert(xlsLoader->getPatterns(),2, 5);
    for(auto iter = languages->begin() ; iter != languages->end() ; ++iter) {
        cout << (*iter)->toString() << endl;
    }
    delete xlsLoader;
    delete languages;
}