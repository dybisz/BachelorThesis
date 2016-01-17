//
// Created by jakub on 12/27/15.
//

#include <gtest/gtest.h>
#include <language/language.h>
#include <language/language_algorithms.h>

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

    language::selectStateCorrespondence(nativeLanguages, foreignLanguages,
                                         statesPerNative, statesPerForeign);

    for(unsigned int i = 0; i < nativeCount; i++){
        Language* language = (*nativeLanguages)[i];
        unsigned int actualStateCount = language->getStates()->size();

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
    for(unsigned int i = 0; i < nativeCount; i++){
        Language* language = new Language(alphabet);
        nativeLanguages->push_back(language);
    }
    for(unsigned int i = 0; i < foreignCount; i++){
        Language* language = new Language(alphabet);
        foreignLanguages->push_back(language);
    }

    language::selectStateCorrespondence(nativeLanguages, foreignLanguages,
                                         statesPerNative, statesPerForeign);
    for(unsigned int i = 0; i < foreignCount; i++){
        Language* language = (*foreignLanguages)[i];
        unsigned int actualStateCount = language->getStates()->size();

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


TEST(LanguageAlgorithms, StateCorrespondence_EachForeignLanguageSameStates0) {
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

    language::selectStateCorrespondence(nativeLanguages, foreignLanguages,
                                         statesPerNative, statesPerForeign);

    for(unsigned int i = 0; i < foreignCount-1; i++){
        for(unsigned int j = i+1; j < foreignCount; j++){
            const std::vector<State*>* states1 =
                    (*foreignLanguages)[i]->getStates();
            const std::vector<State*>* states2 =
                    (*foreignLanguages)[j]->getStates();

            EXPECT_EQ(*((*states1)[0]), *((*states2)[0]));
        }
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


TEST(LanguageAlgorithms, StateCorrespondence_EachForeignLanguageSameStates1) {
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

    language::selectStateCorrespondence(nativeLanguages, foreignLanguages,
                                         statesPerNative, statesPerForeign);

    for(unsigned int i = 0; i < foreignCount-1; i++){
        for(unsigned int j = i+1; j < foreignCount; j++){
            const std::vector<State*>* states1 =
                    (*foreignLanguages)[i]->getStates();
            const std::vector<State*>* states2 =
                    (*foreignLanguages)[j]->getStates();

            EXPECT_EQ(*((*states1)[1]), *((*states2)[1]));
        }
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


TEST(LanguageAlgorithms, StateCorrespondence_EachForeignLanguageSameStates2) {
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

    language::selectStateCorrespondence(nativeLanguages, foreignLanguages,
                                         statesPerNative, statesPerForeign);

    for(unsigned int i = 0; i < foreignCount-1; i++){
        for(unsigned int j = i+1; j < foreignCount; j++){
            const std::vector<State*>* states1 =
                    (*foreignLanguages)[i]->getStates();
            const std::vector<State*>* states2 =
                    (*foreignLanguages)[j]->getStates();

            EXPECT_EQ(*((*states1)[2]), *((*states2)[2]));
        }
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

TEST(LanguageAlgorithms, StateCorrespondence_EachForeignLanguageSameStates3) {
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

    language::selectStateCorrespondence(nativeLanguages, foreignLanguages,
                                         statesPerNative, statesPerForeign);

    for(unsigned int i = 0; i < foreignCount-1; i++){
        for(unsigned int j = i+1; j < foreignCount; j++){
            const std::vector<State*>* states1 =
                    (*foreignLanguages)[i]->getStates();
            const std::vector<State*>* states2 =
                    (*foreignLanguages)[j]->getStates();

            EXPECT_EQ(*((*states1)[3]), *((*states2)[3]));
        }
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

TEST(LanguageAlgorithms, StateCorrespondence_AllNativeDifferentState) {
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

    language::selectStateCorrespondence(nativeLanguages, foreignLanguages,
                                         statesPerNative, statesPerForeign);

    for(unsigned int i = 0; i < nativeCount-1; i++){
        for(unsigned int j = i+1; j < nativeCount; j++){
            const std::vector<State*>* states1 =
                    (*nativeLanguages)[i]->getStates();
            const std::vector<State*>* states2 =
                    (*nativeLanguages)[j]->getStates();

            for(unsigned int s1 = 0; s1 < states1->size(); s1++){
                for(unsigned int s2 = 0; s2 < states2->size(); s2++){
                    EXPECT_NE(*((*states1)[s1]), *((*states2)[s2]));
                }
            }

        }
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
