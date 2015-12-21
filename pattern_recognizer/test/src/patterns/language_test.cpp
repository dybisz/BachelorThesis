//
// Created by dybisz on 21.12.15.
//

#include <gtest/gtest.h>
#include <word.h>
#include <language.h>

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