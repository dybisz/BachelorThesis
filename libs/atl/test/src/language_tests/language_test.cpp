//
// Created by dybisz on 21.12.15.
//

#include <gtest/gtest.h>
#include <language/word.h>
#include <language/language.h>

using namespace std;

TEST(LanguageTest, Constructor_From_Words) {
    int l1[3] = {1,2,3};
    int l2[3] = {6,1,3};
    int l3[3] = {9,8,1};
    Word* w1 = new Word(l1, 3);
    Word* w2 = new Word(l2, 3);
    Word* w3 = new Word(l3, 3);
    Alphabet alphabet(14);
    vector<Word*>  words({w1, w2, w3});

    State* s1 = new State(0);
    State* s2 = new State(1);
    vector<State*> states;
    states.push_back(s1);
    states.push_back(s2);

    Language* language = new Language(words, alphabet, states);

    EXPECT_EQ(*((*language->getWord(0))[2]), 3);
    EXPECT_EQ(*((*language->getWord(2))[1]), 8);
    EXPECT_EQ(((language->getWord(2))), w3);

    delete language;
}

TEST(LanguageTest, Stealing_Words) {
    int l1[3] = {1,2,3};
    int l2[3] = {6,1,3};
    int l3[3] = {9,8,1};
    Word* w1 = new Word(l1, 3);
    Word* w2 = new Word(l2, 3);
    Word* w3 = new Word(l3, 3);
    Alphabet alphabet(14);
    vector<Word*>  words({w1, w2, w3});

    State* s1 = new State(0);
    State* s2 = new State(1);
    vector<State*> states;
    states.push_back(s1);
    states.push_back(s2);

    Language* language = new Language(words, alphabet, states);
    Word* stolenWord = language->stealLastWord();

    EXPECT_EQ(*((*stolenWord)[0]), 9);
    EXPECT_EQ(*((*stolenWord)[1]), 8);
    EXPECT_EQ(*((*stolenWord)[2]), 1);
    EXPECT_EQ(language->size(), 2);

    delete stolenWord;
    delete language;
}

TEST(LanguageTest, Partiall_Init) {
    int l1[3] = {1,2,3};
    int l2[3] = {6,1,3};
    int l3[3] = {9,8,1};
    Word* w1 = new Word(l1, 3);
    Word* w2 = new Word(l2, 3);
    Word* w3 = new Word(l3, 3);
    Alphabet alphabet(14);
    vector<Word*>  words({w1, w2, w3});

    State* s1 = new State(0);
    State* s2 = new State(1);
    vector<State*> states;
    states.push_back(s1);
    states.push_back(s2);

    Language* L1 = new Language(words, alphabet, states);
    words.pop_back();
    Language* L2 = new Language(words, L1);

    EXPECT_EQ(L2->size(), 2);
    EXPECT_EQ(L2->getAlphabet(), alphabet);
    EXPECT_EQ((*(L2->getStates())).size(), 2);

    delete L1;
    delete L2;
}

TEST(Language, SetStatesSmallCount_CorrectSizeCount) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    unsigned int expectedStateCount = 3;

    State* correctState1 = new State(0);
    State* correctState2 = new State(1);
    State* correctState3 = new State(2);

    std::vector<State*> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    unsigned int actualStateCount = language.getStates()->size();

    EXPECT_EQ(expectedStateCount, actualStateCount);
}

TEST(Language, SetStatesBigCount_CorrectSizeCount) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    unsigned int expectedStateCount = 50;
    std::vector<State*> states;

    for(unsigned int i = 0; i < expectedStateCount; i++){
        State* correctState1 = new State(i);
        states.push_back(correctState1);
    }

    language.setStates(states);

    unsigned int actualStateCount = language.getStates()->size();

    EXPECT_EQ(expectedStateCount, actualStateCount);
}


TEST(Language, SetStates_IsCorrespodingToCorrectState1) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    State* correctState1 = new State(0);
    State* correctState2 = new State(1);
    State* correctState3 = new State(2);

    std::vector<State*> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    bool expectedValue = true;
    bool actualValue = language.isCorrespondingState(correctState1);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(Language, SetStates_IsCorrespodingToCorrectState2) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    State* correctState1 = new State(0);
    State* correctState2 = new State(1);
    State* correctState3 = new State(2);

    std::vector<State*> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    bool expectedValue = true;
    bool actualValue = language.isCorrespondingState(correctState2);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(Language, SetStates_IsCorrespodingToCorrectState3) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    State* correctState1 = new State(0);
    State* correctState2 = new State(1);
    State* correctState3 = new State(2);

    std::vector<State*> states{correctState1,
                               correctState2,
                               correctState3};
    language.setStates(states);

    bool expectedValue = true;
    bool actualValue = language.isCorrespondingState(correctState3);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(Language, SetStates_IsNotCorrespodingToCorrectState1) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);
    State* correctState1 = new State(0);
    State* correctState2 = new State(1);
    State* correctState3 = new State(2);
    State* incorectState = new State(3);

    std::vector<State*> states{correctState1,
                               correctState2,
                               correctState3};


    language.setStates(states);

    bool expectedValue = false;
    bool actualValue = language.isCorrespondingState(incorectState);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(Language, SetStates_IsNotCorrespodingToCorrectState2) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    State* correctState1 = new State(0);
    State* incorectState1 = new State(1);
    State* correctState2 = new State(2);
    State* correctState3 = new State(3);
    State* incorectState2 = new State(4);

    std::vector<State*> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    bool expectedValue = false;
    bool actualValue = language.isCorrespondingState(incorectState1);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(Language, AddWord_SizeIncreased) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    Word* word = new Word();
    language.addWord(word);

    unsigned int expectedSize = 1;
    unsigned int actualSize = language.size();

    EXPECT_EQ(expectedSize, actualSize);
}
