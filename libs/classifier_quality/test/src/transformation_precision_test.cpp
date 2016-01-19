//
// Created by jakub on 1/17/16.
//

#include <gtest/gtest.h>

#include "transformation_precision.h"

TEST(TransformationPrecision,
     ObjectPatternWithThreeFeature_AlphabetSizeOne_PrecisionIs1by3) {
    double feature1 = 1.0f;
    double feature2 = 5.0f;
    double feature3 = 10.0f;

    FeaturesVector* featuresVector1 = new FeaturesVector();
    featuresVector1->appendSymbol(feature1);
    featuresVector1->appendSymbol(feature2);
    featuresVector1->appendSymbol(feature3);

    FeaturesVector* featuresVector2 = new FeaturesVector();
    featuresVector2->appendSymbol(feature1);
    featuresVector2->appendSymbol(feature2);
    featuresVector2->appendSymbol(feature3);

    FeaturesVector* featuresVector3 = new FeaturesVector();
    featuresVector3->appendSymbol(feature1);
    featuresVector3->appendSymbol(feature2);
    featuresVector3->appendSymbol(feature3);

    int label = 0;
    Pattern pattern(label);
    pattern.appendFeatureVector(featuresVector1);
    pattern.appendFeatureVector(featuresVector2);
    pattern.appendFeatureVector(featuresVector3);

    int alphabetSize = 1;

    double expectedValue = (double) 1/3;
    double actualValue = quality::computeTransformationPrecision(pattern,
                                                                 alphabetSize);
    EXPECT_EQ(expectedValue, actualValue);
}