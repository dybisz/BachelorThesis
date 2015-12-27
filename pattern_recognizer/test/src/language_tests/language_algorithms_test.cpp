//
// Created by jakub on 12/27/15.
//

#include <gtest/gtest.h>
#include <language.h>
#include <language_algorithms.h>

TEST(LanguageAlgorithms, StateCorrespondence_NativeProperNumberOfStates) {
    unsigned int nativeCount = 4;
    unsigned int foreignCount = 3;

    unsigned int statesPerNative = 5;
    unsigned int statesPerForeign = 4;

    unsigned int alphabetSize = 3;

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

    languages::selectStateCorrespondence(nativeLanguages, foreignLanguages,
                                         statesPerNative, statesPerForeign);

    for(unsigned int i = 0; i < nativeCount; i++){
        Language* language = (*nativeLanguages)[i];
        unsigned int actualStateCount = language->getStatesPtr()->size();

        EXPECT_EQ(statesPerNative, actualStateCount);
    }

    for(unsigned int i = 0; i < nativeCount; i++){
        delete (*nativeLanguages)[i];
    }
    std::cout << "0" << std::endl;
    for(unsigned int i = 0; i < foreignCount; i++){
        delete (*foreignLanguages)[i];
    }
    std::cout << "1" << std::endl;
    delete nativeLanguages;
    delete foreignLanguages;
}

TEST(LanguageAlgorithms, StateCorrespondence_ForeignProperNumberOfStates) {
    unsigned int nativeCount = 4;
    unsigned int foreignCount = 3;

    unsigned int statesPerNative = 5;
    unsigned int statesPerForeign = 4;

    unsigned int alphabetSize = 3;

    std::vector<Language*> *nativeLanguages = new std::vector<Language*>;
    std::vector<Language*> *foreignLanguages = new std::vector<Language*>;
    Alphabet alphabet(alphabetSize);
    std::cout << "1" << std::endl;
    for(unsigned int i = 0; i < nativeCount; i++){
        Language* language = new Language(alphabet);
        nativeLanguages->push_back(language);
    }
    std::cout << "1.1" << std::endl;
    for(unsigned int i = 0; i < foreignCount; i++){
        std::cout << "1.2" << std::endl;
        Language* language = new Language(alphabet);
        std::cout << "1.3" << std::endl;
        foreignLanguages->push_back(language);
    }
    std::cout << "2" << std::endl;

    std::cout << "Before " << std::endl;
    languages::selectStateCorrespondence(nativeLanguages, foreignLanguages,
                                         statesPerNative, statesPerForeign);
    std::cout << "After" << std::endl;
    for(unsigned int i = 0; i < foreignCount; i++){
        Language* language = (*foreignLanguages)[i];
        unsigned int actualStateCount = language->getStatesPtr()->size();

        EXPECT_EQ(statesPerForeign, actualStateCount);
    }

    for(unsigned int i = 0; i < nativeCount; i++){
        delete (*nativeLanguages)[i];
    }
    for(unsigned int i = 0; i < foreignCount; i++){
        delete (*foreignLanguages)[i];
    }
    delete nativeLanguages;
    delete foreignLanguages;
}