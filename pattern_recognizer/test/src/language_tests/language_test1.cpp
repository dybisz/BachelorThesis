//
// Created by jakub on 12/27/15.
//

#include <gtest/gtest.h>
#include <alphabet.h>
#include <language.h>

TEST(Language, SetStatesSmallCount_CorrectSizeCount) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    unsigned int expectedStateCount = 3;

    State correctState1(0);
    State correctState2(1);
    State correctState3(2);

    std::vector<State> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    unsigned int actualStateCount = language.getStatesPtr()->size();

    EXPECT_EQ(expectedStateCount, actualStateCount);
}

TEST(Language, SetStatesBigCount_CorrectSizeCount) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    unsigned int expectedStateCount = 50;
    std::vector<State> states;

    for(unsigned int i = 0; i < expectedStateCount; i++){
        State correctState1(i);
        states.push_back(correctState1);
    }

    language.setStates(states);

    unsigned int actualStateCount = language.getStatesPtr()->size();

    EXPECT_EQ(expectedStateCount, actualStateCount);
}


TEST(Language, SetStates_IsCorrespodingToCorrectState1) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    State correctState1(0);
    State correctState2(1);
    State correctState3(2);

    std::vector<State> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    bool expectedValue = true;
    bool actualValue = language.isCorrespondingStatePtr(&correctState1);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(Language, SetStates_IsCorrespodingToCorrectState2) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    State correctState1(0);
    State correctState2(1);
    State correctState3(2);

    std::vector<State> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    bool expectedValue = true;
    bool actualValue = language.isCorrespondingStatePtr(&correctState2);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(Language, SetStates_IsCorrespodingToCorrectState3) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    State correctState1(0);
    State correctState2(1);
    State correctState3(2);

    std::vector<State> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    bool expectedValue = true;
    bool actualValue = language.isCorrespondingStatePtr(&correctState3);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(Language, SetStates_IsNotCorrespodingToCorrectState1) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    State correctState1(0);
    State correctState2(1);
    State correctState3(2);
    State incorectState(3);

    std::vector<State> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    bool expectedValue = false;
    bool actualValue = language.isCorrespondingStatePtr(&incorectState);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(Language, SetStates_IsNotCorrespodingToCorrectState2) {
    unsigned int alhpabetSize = 2;
    Alphabet alphabet(alhpabetSize);

    Language language(alphabet);

    State correctState1(0);
    State incorectState1(1);
    State correctState2(2);
    State correctState3(3);
    State incorectState2(4);

    std::vector<State> states{correctState1,
                               correctState2,
                               correctState3};

    language.setStates(states);

    bool expectedValue = false;
    bool actualValue = language.isCorrespondingStatePtr(&incorectState1);

    EXPECT_EQ(expectedValue, actualValue);
}