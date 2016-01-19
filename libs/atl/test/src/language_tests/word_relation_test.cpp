//
// Created by jakub on 1/19/16.
//


#include <gtest/gtest.h>
#include <language/word.h>
#include <language/word_relations.h>


TEST(WordRelation_HammingDistance, WordSizedDontMatch_ThrowsException) {
    Word word1;
    word1.appendSymbol(0);
    word1.appendSymbol(1);
    Word word2;
    word2.appendSymbol(2);
    EXPECT_ANY_THROW(word::hammingDistance(word1, word2));
}

TEST(WordRelation_HammingDistance,
        WordsWithDifferentSymbol_HammingDistanceEqualsOne) {
    Word word1;
    word1.appendSymbol(0);
    word1.appendSymbol(1);
    Word word2;
    word2.appendSymbol(0);
    word2.appendSymbol(2);

    int expectedHammingDistance = 1;
    int actualHammingDistance = word::hammingDistance(word1, word2);

    EXPECT_EQ(expectedHammingDistance, actualHammingDistance);
}

TEST(WordRelation_HammingDistance,
     EqualWords_HammingDistanceEqualsZero) {
    Word word1;
    word1.appendSymbol(0);
    word1.appendSymbol(1);
    Word word2;
    word2.appendSymbol(0);
    word2.appendSymbol(1);

    int expectedHammingDistance = 0;
    int actualHammingDistance = word::hammingDistance(word1, word2);

    EXPECT_EQ(expectedHammingDistance, actualHammingDistance);
}

TEST(WordRelation_Similarity,
     WordsCompletelyDifferent_SimilarityZero) {
    Word word1;
    word1.appendSymbol(0);
    word1.appendSymbol(1);
    Word word2;
    word2.appendSymbol(2);
    word2.appendSymbol(4);

    double expectedSimilarity = 0.0f;
    double actualSimilarity = word::similarity(word1, word2);

    EXPECT_EQ(expectedSimilarity, actualSimilarity);
}


TEST(WordRelation_Similarity,
     WordsEqual_SimilarityOne) {
    Word word1;
    word1.appendSymbol(0);
    word1.appendSymbol(1);
    Word word2;
    word2.appendSymbol(0);
    word2.appendSymbol(1);

    double expectedSimilarity = 1;
    double actualSimilarity = word::similarity(word1, word2);

    EXPECT_EQ(expectedSimilarity, actualSimilarity);
}

TEST(WordRelation_Similarity,
     WordsHalfEqual_SimilarityHalf) {
    Word word1;
    word1.appendSymbol(0);
    word1.appendSymbol(1);
    Word word2;
    word2.appendSymbol(0);
    word2.appendSymbol(2);

    double expectedSimilarity = 0.5f;
    double actualSimilarity = word::similarity(word1, word2);

    EXPECT_EQ(expectedSimilarity, actualSimilarity);
}