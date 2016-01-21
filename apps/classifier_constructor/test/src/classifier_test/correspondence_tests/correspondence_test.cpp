//
// Created by jakub on 1/21/16.
//

#include <gtest/gtest.h>
#include <classifier_constructor/classifier/correspondence/correspondence.h>

TEST(StateCorrespodence,
     LabelNotInCorrespondence_GetStates_ExceptionThrown){
    Correspondence stateCorrespodence;

    Label label(0);

    EXPECT_ANY_THROW(stateCorrespodence.getStates(label));
}


TEST(StateCorrespodence,
     EmptyCorrespodence_AddedNewCorrespondence_StateCorrectlyCorresponding){
    Correspondence stateCorrespodence;

    Label label(2);
    State state(0);

    stateCorrespodence.addCorrespondence(label, state);

    bool expectedValue = true;
    bool actualValue = stateCorrespodence.isCorresponding(label, state);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(StateCorrespodence,
     NonEmptyCorrespodence_AddedNewCorrespondence_StateCorrectlyCorresponding){
    Correspondence stateCorrespodence;

    Label label1(0);
    State state11(0);
    State state12(1);

    Label label2(1);
    State state21(2);
    State state22(3);

    stateCorrespodence.addCorrespondence(label1, state11);
    stateCorrespodence.addCorrespondence(label1, state12);

    stateCorrespodence.addCorrespondence(label2, state21);
    stateCorrespodence.addCorrespondence(label2, state22);

    bool expectedValue = true;
    bool actualValue = stateCorrespodence.isCorresponding(label2, state21);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(StateCorrespodence,
     LabelAlreadyInCorresponding_AddedNewState_CorrectlyCorresponding){
    Correspondence stateCorrespodence;

    Label label1(0);
    State state11(0);
    State state12(1);

    stateCorrespodence.addCorrespondence(label1, state11);
    stateCorrespodence.addCorrespondence(label1, state12);


    bool expectedValue = true;
    bool actualValue = stateCorrespodence.isCorresponding(label1, state12);

    EXPECT_EQ(expectedValue, actualValue);
}

TEST(StateCorrespodence,
     LabelAlreadyInCorresponding_NotAddedState_CorrectlyNotCorresponding){
    Correspondence stateCorrespodence;

    Label label1(0);
    State state11(0);
    State state12(1);

    State state3(2);

    stateCorrespodence.addCorrespondence(label1, state11);
    stateCorrespodence.addCorrespondence(label1, state12);

    bool expectedValue = false;
    bool actualValue = stateCorrespodence.isCorresponding(label1, state3);

    EXPECT_EQ(expectedValue, actualValue);
}