//
// Created by dybisz on 20.12.15.
//

#include <gtest/gtest.h>
#include <pattern.h>
#include <patterns_to_languages.h>
#include <xls_loader.h>

using namespace std;
using namespace patterns_to_languages;

string DATA_PATH2 = "./res/fv_example.xls";

TEST(PatternsToLanguages, Pattern_Init) {
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH2);
    vector<Language *> * languages = convert(xlsLoader->getPatterns(),2, 5);
    delete xlsLoader;
    delete languages;
}

TEST(PatternsToLanguages, Pattern_Wrong_Input) {
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH2);
    vector<Language *> * languages = NULL;
    ASSERT_ANY_THROW(languages = convert(xlsLoader->getPatterns(),-1, -1));
    if(languages != NULL) delete languages;
    delete xlsLoader;
}
/*
TEST(PatternsToLanguages, CovertToLanguages_CorrectLanguageCount) {
    int alphabetSize = 2;
    unsigned int expectedLanguageCount = 3;
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH2);
    vector<Language *> * languages = convert(xlsLoader->getPatterns(),
                                             alphabetSize);

    unsigned int actualLanguageCount = languages->size();

    EXPECT_EQ(expectedLanguageCount, actualLanguageCount);

    delete xlsLoader;
    for(unsigned int i = 0; i < languages->size(); i++){
        delete (*languages)[i];
    }
    delete languages;
}

TEST(PatternsToLanguages, CovertToLanguages_CorrectAlphabetSize) {
    int expectedAlphabetSize = 2;

    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH2);
    vector<Language *> * languages = convert(xlsLoader->getPatterns(),
                                             expectedAlphabetSize);

    for(unsigned int i = 0; i < languages->size(); i++){
        unsigned int actualAlphabetSize = (*languages)[i]->getAlphabet().size();

        EXPECT_EQ(expectedAlphabetSize, actualAlphabetSize);
    }

    delete xlsLoader;

    for(unsigned int i = 0; i < languages->size(); i++){
        delete (*languages)[i];
    }
    delete languages;
}*/