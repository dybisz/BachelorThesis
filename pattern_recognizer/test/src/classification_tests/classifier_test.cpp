//
// Created by jakub on 12/22/15.
//

#include <gtest/gtest.h>
#include <classifier.h>
#include <language.h>

TEST(Classification, ClassifierSmallLanguage_ProperStateCount) {
    unsigned int nativeCount = 4;
    unsigned int foreignCount = 3;

    unsigned int statesPerNative = 5;
    unsigned int statesPerForeign = 4;

    unsigned int alphabetSize = 3;

    unsigned int expectedStateCount = nativeCount*statesPerNative+
                            statesPerForeign;

    std::vector<Language*> *nativeLanguages = new std::vector<Language*>;
    std::vector<Language*> *foreignLanguages = new std::vector<Language*>;
    Alphabet alphabet(alphabetSize);

    for(unsigned int i = 0; i < nativeCount; i++){
        Language* language = new Language(alphabet);
        nativeLanguages->push_back(language);
    }
    for(unsigned int i = 0; i < foreignCount; i++){
        Language* language = new Language(alphabet);
        foreignLanguages->push_back(language);
    }

    Classifier* classifier = new Classifier(nativeLanguages, foreignLanguages,
                                            statesPerNative,statesPerForeign,
                                            alphabetSize);

    unsigned int actualStateCount = classifier->getStateCount();

    EXPECT_EQ(expectedStateCount, actualStateCount);

    delete classifier;
}

TEST(Classification, ClassifierBigLanguage_ProperStateCount) {
    unsigned int nativeCount = 100;
    unsigned int foreignCount = 200;

    unsigned int statesPerNative = 25;
    unsigned int statesPerForeign = 26;

    unsigned int alphabetSize = 7;

    unsigned int expectedStateCount = nativeCount*statesPerNative+
                                      statesPerForeign;

    std::vector<Language*> *nativeLanguages = new std::vector<Language*>;
    std::vector<Language*> *foreignLanguages = new std::vector<Language*>;
    Alphabet alphabet(alphabetSize);

    for(unsigned int i = 0; i < nativeCount; i++){
        Language* language = new Language(alphabet);
        nativeLanguages->push_back(language);
    }
    for(unsigned int i = 0; i < foreignCount; i++){
        Language* language = new Language(alphabet);
        foreignLanguages->push_back(language);
    }

    Classifier* classifier = new Classifier(nativeLanguages, foreignLanguages,
                                            statesPerNative,statesPerForeign,
                                            alphabetSize);

    unsigned int actualStateCount = classifier->getStateCount();

    EXPECT_EQ(expectedStateCount, actualStateCount);

    delete classifier;
}