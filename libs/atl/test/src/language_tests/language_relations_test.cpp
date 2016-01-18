//
// Created by jakub on 1/17/16.
//

#include <gtest/gtest.h>
#include <language/alphabet.h>
#include <language/language.h>
#include "language/language_relations.h"

using namespace std;

TEST(LanguageRelations_Intersection,
     IntersectionDifferentAlphabets_InvalidArgumentException) {
    int alphabetSize1 = 5;
    int alphabetSize2 = 2;

    Alphabet alphabet1(alphabetSize1);
    Alphabet alphabet2(alphabetSize2);

    Language language1(alphabet1);
    Language language2(alphabet2);

    EXPECT_ANY_THROW(language::intersection(language1, language2));
}

TEST(LanguageRelations_Intersection,
     TwoLanguagesWithOneIntersectingWord_OneWordInIntersectingLanguage) {
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

    language1.addWord(word1);
    language1.addWord(word2);

    language2.addWord(word3);

    int expectedLanguageSize = 1;

    Language* intersectingLanguage = language::intersection(language1,
                                                            language2);

    int actualLanguageSize = intersectingLanguage->size();

    delete intersectingLanguage;

    EXPECT_EQ(expectedLanguageSize, actualLanguageSize);

}

TEST(LanguageRelations_Intersection,
     TwoLanguagesWithOneIntersectingWord_IntersectingLanguageContainsThatWord) {
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

    language1.addWord(word1);
    language1.addWord(word2);

    language2.addWord(word3);

    int expectedLanguageSize = 1;

    Language* intersectingLanguage = language::intersection(language1,
                                                            language2);

    Word* intersctingWord = intersectingLanguage->getWord(0);


    EXPECT_EQ(*word3, *intersctingWord);

}

TEST(LanguageRelations_Intersection,
     TwoLanguagesWithNoIntersectingWords_IntersectingLanguageIsEmpty) {
    int alphabetSize1 = 5;
    int alphabetSize2 = 5;

    Alphabet alphabet1(alphabetSize1);
    Alphabet alphabet2(alphabetSize2);

    Language language1(alphabet1);
    Language language2(alphabet2);

    std::vector<int> wordEntries1{1, 2, 3};
    std::vector<int> wordEntries2{3, 2, 1};
    std::vector<int> wordEntries3{1, 2, 4};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language1.addWord(word1);
    language1.addWord(word2);

    language2.addWord(word3);

    int expectedLanguageSize = 0;

    Language* intersectingLanguage = language::intersection(language1,
                                                            language2);

    int actualLanguageSize = intersectingLanguage->size();

    delete intersectingLanguage;

    EXPECT_EQ(expectedLanguageSize, actualLanguageSize);

}


TEST(LanguageRelations_IntersectionSum,
     LanguagesSingleWord_WithAllSameWord_IntersectionSumEqualToOne) {
    int alphabetSize1 = 5;

    Alphabet alphabet1(alphabetSize1);

    Language language1(alphabet1);
    Language language2(alphabet1);
    Language language3(alphabet1);

    std::vector<int> wordEntries1{1, 2, 3};
    std::vector<int> wordEntries2{1, 2, 3};
    std::vector<int> wordEntries3{1, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language1.addWord(word1);
    language2.addWord(word2);
    language3.addWord(word3);

    std::vector<Language*> languages{&language1,
                                     &language2,
                                     &language3};

    int expectedLanguageSize = 1;

    Language* intersectingSumLanguage = language::intersectionSum(&languages);

    int actualLanguageSize = intersectingSumLanguage->size();

    delete intersectingSumLanguage;

    EXPECT_EQ(expectedLanguageSize, actualLanguageSize);
}

TEST(LanguageRelations_IntersectionSum,
     LanguagesWithSingleWordWithOneEqualWord_IntersectionSumEqualZero) {
    int alphabetSize1 = 5;

    Alphabet alphabet1(alphabetSize1);

    Language language1(alphabet1);
    Language language2(alphabet1);
    Language language3(alphabet1);

    std::vector<int> wordEntries1{1, 2, 3};
    std::vector<int> wordEntries2{1, 2, 3};
    std::vector<int> wordEntries3{2, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language1.addWord(word1);
    language2.addWord(word2);
    language3.addWord(word3);

    std::vector<Language*> languages{&language1,
                                     &language2,
                                     &language3};

    int expectedLanguageSize = 0;

    Language* intersectingSumLanguage = language::intersectionSum(&languages);

    int actualLanguageSize = intersectingSumLanguage->size();

    delete intersectingSumLanguage;

    EXPECT_EQ(expectedLanguageSize, actualLanguageSize);
}

TEST(LanguageRelations_IntersectionSum,
     LanguagesWithNoEqualWords_IntersectionSumEqualZero) {
    int alphabetSize1 = 5;

    Alphabet alphabet1(alphabetSize1);

    Language language1(alphabet1);
    Language language2(alphabet1);
    Language language3(alphabet1);

    std::vector<int> wordEntries1{3, 2, 3};
    std::vector<int> wordEntries2{1, 2, 3};
    std::vector<int> wordEntries3{2, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language1.addWord(word1);
    language2.addWord(word2);
    language3.addWord(word3);

    std::vector<Language*> languages{&language1,
                                     &language2,
                                     &language3};

    int expectedLanguageSize = 0;

    Language* intersectingSumLanguage = language::intersectionSum(&languages);

    int actualLanguageSize = intersectingSumLanguage->size();

    delete intersectingSumLanguage;

    EXPECT_EQ(expectedLanguageSize, actualLanguageSize);
}

TEST(LanguageRelations_IntersectionSum,
     LanguagesMultiWordWithOneIntersectingWord_IntersectionSumEqualOne) {
    int alphabetSize1 = 5;

    Alphabet alphabet1(alphabetSize1);

    Language language1(alphabet1);
    Language language2(alphabet1);
    Language language3(alphabet1);

    std::vector<int> wordEntries1{3, 2, 3};
    std::vector<int> wordEntries2{1, 2, 3};
    std::vector<int> wordEntries3{2, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language1.addWord(word1);
    language1.addWord(word2);
    language1.addWord(word3);

    language2.addWord(new Word(word1));
    language2.addWord(new Word(word2));

    language3.addWord(new Word(word2));
    language3.addWord(new Word(word3));

    std::vector<Language*> languages{&language1,
                                     &language2,
                                     &language3};

    int expectedLanguageSize = 1;

    Language* intersectingSumLanguage = language::intersectionSum(&languages);

    int actualLanguageSize = intersectingSumLanguage->size();

    delete intersectingSumLanguage;

    EXPECT_EQ(expectedLanguageSize, actualLanguageSize);
}

TEST(LanguageRelations_IntersectionSum,
     LanguagesMultiWordWithOneIntersectingWord_IntersectionHasProperWord) {
    int alphabetSize1 = 5;

    Alphabet alphabet1(alphabetSize1);

    Language language1(alphabet1);
    Language language2(alphabet1);
    Language language3(alphabet1);

    std::vector<int> wordEntries1{3, 2, 3};
    std::vector<int> wordEntries2{1, 2, 3};
    std::vector<int> wordEntries3{2, 2, 3};

    Word* word1 = new Word(wordEntries1);
    Word* word2 = new Word(wordEntries2);
    Word* word3 = new Word(wordEntries3);

    language1.addWord(word1);
    language1.addWord(word2);
    language1.addWord(word3);

    language2.addWord(new Word(word1));
    language2.addWord(new Word(word2));

    language3.addWord(new Word(word2));
    language3.addWord(new Word(word3));

    std::vector<Language*> languages{&language1,
                                     &language2,
                                     &language3};

    int expectedLanguageSize = 1;

    Language* intersectingSumLanguage = language::intersectionSum(&languages);

    Word* actualWord = intersectingSumLanguage->getWord(0);

    EXPECT_EQ(*word2, *actualWord);

    delete intersectingSumLanguage;
}


TEST(LanguageRelation_EqualAlphabets,
      TwoLanguagesWithEqualAlphabets_ReturnTrue){

    int alphabetSize1 = 5;
    int alphabetSize2 = 5;

    Alphabet alphabet1(alphabetSize1);
    Alphabet alphabet2(alphabetSize2);

    Language language1(alphabet1);
    Language language2(alphabet2);

    bool expectedValue = true;
    bool actualValue = language::equalAlphabets(language1, language2);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(LanguageRelation_EqualAlphabets,
     TwoLanguagesWithDifferentSizeAlphabets_ThrowsInvalidArgumentException){

    int alphabetSize1 = 5;
    int alphabetSize2 = 4;

    Alphabet alphabet1(alphabetSize1);
    Alphabet alphabet2(alphabetSize2);

    Language language1(alphabet1);
    Language language2(alphabet2);

    EXPECT_ANY_THROW(language::equalAlphabets(language1, language2));
}

TEST(LanguageRelation_EqualAlphabets,
     VectorOfLanguages_AllWithEqualAlphabet_ReturnTrue){

    int alphabetSize1 = 5;

    Alphabet alphabet1(alphabetSize1);

    Language language1(alphabet1);
    Language language2(alphabet1);
    Language language3(alphabet1);
    Language language4(alphabet1);

    std::vector<Language*> languages{&language1, &language2,
                                     &language3, &language4};

    bool expectedValue = true;
    bool actualValue = language::equalAlphabets(&languages);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(LanguageRelation_EqualAlphabets,
     VectorOfLanguages_AllWithDiffSizeAlphabet_ThrowsInvalidArgumentException){

    int alphabetSize1 = 5;
    int alphabetSize2 = 4;

    Alphabet alphabet1(alphabetSize1);
    Alphabet alphabet2(alphabetSize2);

    Language language1(alphabet1);
    Language language2(alphabet1);
    Language language3(alphabet2);
    Language language4(alphabet1);

    std::vector<Language*> languages{&language1, &language2,
                                     &language3, &language4};

    EXPECT_ANY_THROW(language::equalAlphabets(&languages));
}