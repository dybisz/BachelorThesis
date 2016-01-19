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

TEST(Language, EmptyLangauge_AppendLanguage_SameSize) {
    int alphabetSize1 = 5;
    int alphabetSize2 = 5;

    Alphabet alphabet1(alphabetSize1);
    Alphabet alphabet2(alphabetSize2);

    Language language1(alphabet1);
    Language language2(alphabet2);

    std::vector<int> wordEntries1{1, 2, 3};
    std::vector<int> wordEntries2{3, 2, 1};
    std::vector<int> wordEntries3{1, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language2.addWord(word1);
    language2.addWord(word2);
    language2.addWord(word3);

    language1.append(language2);

    int expectedSize = 3;

    int actualSize = language1.size();

    EXPECT_EQ(expectedSize, actualSize);
}

TEST(Language, LanguageContainsTwoEqualWords_OccurenceCounterEqualsTwo) {
    int alphabetSize1 = 5;

    Alphabet alphabet(alphabetSize1);

    Language language(alphabet);

    std::vector<int> wordEntries1{1, 2, 3};
    std::vector<int> wordEntries2{3, 2, 3};
    std::vector<int> wordEntries3{1, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language.addWord(word1);
    language.addWord(word2);
    language.addWord(word3);

    int expectedOccurrenceCounter = 2;

    int actualOccurrenceCounter = language.numberOfOccurrences(*word1);

    EXPECT_EQ(expectedOccurrenceCounter, actualOccurrenceCounter);
}

TEST(Language, LanguageContainsTwoEqualWords_OccurenceCounterEqualsOne) {
    int alphabetSize1 = 5;

    Alphabet alphabet(alphabetSize1);

    Language language(alphabet);

    std::vector<int> wordEntries1{1, 2, 3};
    std::vector<int> wordEntries2{3, 2, 3};
    std::vector<int> wordEntries3{1, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language.addWord(word1);
    language.addWord(word2);
    language.addWord(word3);

    int expectedOccurrenceCounter = 1;

    int actualOccurrenceCounter = language.numberOfOccurrences(*word2);

    EXPECT_EQ(expectedOccurrenceCounter, actualOccurrenceCounter);
}

TEST(Language,
     LanguageContainsTwoEqualWords_OccurrenceInputIsNotContained_ReturnZero) {
    int alphabetSize1 = 5;

    Alphabet alphabet(alphabetSize1);

    Language language(alphabet);

    std::vector<int> wordEntries1{1, 2, 3};
    std::vector<int> wordEntries2{3, 2, 3};
    std::vector<int> wordEntries3{1, 2, 3};

    std::vector<int> wordEntries4{3, 3, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    Word* word4 = new Word(wordEntries4);

    language.addWord(word1);
    language.addWord(word2);
    language.addWord(word3);

    int expectedOccurrenceCounter = 0;

    int actualOccurrenceCounter = language.numberOfOccurrences(*word4);

    EXPECT_EQ(expectedOccurrenceCounter, actualOccurrenceCounter);

    delete word4;
}

TEST(Language,
     LanguageContainsTwoDuplicateWords_SizeShorterByOne) {
    int alphabetSize1 = 5;

    Alphabet alphabet(alphabetSize1);

    Language language(alphabet);

    std::vector<int> wordEntries1{1, 2, 3};
    std::vector<int> wordEntries2{3, 2, 3};
    std::vector<int> wordEntries3{1, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language.addWord(word1);
    language.addWord(word2);
    language.addWord(word3);

    int expectedLanguageWithoutDuplicatesSize = 2;

    language.removeDuplicates();

    int actualLanguageWithoutDuplicatesSize = language.size();

    EXPECT_EQ(expectedLanguageWithoutDuplicatesSize,
              actualLanguageWithoutDuplicatesSize);
}

TEST(Language,
     LanguageContainsAllDuplicateWords_NewSizeEqualOne) {
    int alphabetSize1 = 5;

    Alphabet alphabet(alphabetSize1);

    Language language(alphabet);

    std::vector<int> wordEntries1{1, 2, 3};
    std::vector<int> wordEntries2{1, 2, 3};
    std::vector<int> wordEntries3{1, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language.addWord(word1);
    language.addWord(word2);
    language.addWord(word3);

    int expectedLanguageWithoutDuplicatesSize = 1;

    language.removeDuplicates();

    int actualLanguageWithoutDuplicatesSize = language.size();

    EXPECT_EQ(expectedLanguageWithoutDuplicatesSize,
              actualLanguageWithoutDuplicatesSize);
}

TEST(Language,
     LanguageContainsNoDuplicateWords_NoChangeInSize) {
    int alphabetSize1 = 5;

    Alphabet alphabet(alphabetSize1);

    Language language(alphabet);

    std::vector<int> wordEntries1{2, 2, 3};
    std::vector<int> wordEntries2{3, 2, 3};
    std::vector<int> wordEntries3{1, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language.addWord(word1);
    language.addWord(word2);
    language.addWord(word3);

    int expectedLanguageWithoutDuplicatesSize = 3;

    language.removeDuplicates();

    int actualLanguageWithoutDuplicatesSize = language.size();

    EXPECT_EQ(expectedLanguageWithoutDuplicatesSize,
              actualLanguageWithoutDuplicatesSize);
}