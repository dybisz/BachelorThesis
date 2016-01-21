//
// Created by jakub on 1/21/16.
//

#include <gtest/gtest.h>
#include <classifier_constructor/classifier/correspondence/correspondence.h>
#include <classifier_constructor/classifier/correspondence/serialization/corresp_serialization.h>

TEST(CorrespondenceSerialization,
CorrespondenceSavedToString_SavedStringEqualToTheOriginal){
    Correspondence correspondence;

    Label label1(1);
    Label label2(2);
    Label label3(3);

    State state1(1);
    State state2(2);
    State state3(3);
    State state4(4);
    State state5(5);

    correspondence.addCorrespondence(label1, state1);
    correspondence.addCorrespondence(label1, state2);

    correspondence.addCorrespondence(label2, state3);

    correspondence.addCorrespondence(label3, state4);
    correspondence.addCorrespondence(label3, state5);

    std::string expectedString = "1,1,2;2,3;3,4,5";

    std::string actualString =
            corresp_serialization::saveCorrespondenceToString(correspondence);

    EXPECT_EQ(expectedString, actualString);
}

TEST(CorrespondenceSerialization,
     CorrespondenceSavedToString_LoadedBackToObject_EqualCorrespondence){
    Correspondence correspondence;

    Label label1(1);
    Label label2(2);
    Label label3(3);

    State state1(1);
    State state2(2);
    State state3(3);
    State state4(4);
    State state5(5);

    correspondence.addCorrespondence(label1, state1);
    correspondence.addCorrespondence(label1, state2);

    correspondence.addCorrespondence(label2, state3);

    correspondence.addCorrespondence(label3, state4);
    correspondence.addCorrespondence(label3, state5);

    std::string correspondenceString =
            corresp_serialization::saveCorrespondenceToString(correspondence);

    Correspondence loadedCorrespondence =
            corresp_serialization::loadCorrespondenceFromString
                    (correspondenceString);

    bool expectedValue = true;
    bool actualValue = loadedCorrespondence.isCorresponding(label1, state1);
    EXPECT_EQ(expectedValue, actualValue);

    actualValue = loadedCorrespondence.isCorresponding(label1, state2);
    EXPECT_EQ(expectedValue, actualValue);

    actualValue = loadedCorrespondence.isCorresponding(label2, state3);
    EXPECT_EQ(expectedValue, actualValue);

    actualValue = loadedCorrespondence.isCorresponding(label3, state4);
    EXPECT_EQ(expectedValue, actualValue);

    actualValue = loadedCorrespondence.isCorresponding(label3, state5);
    EXPECT_EQ(expectedValue, actualValue);
}