//
// Created by jakub on 12/23/15.
//

#include <gtest/gtest.h>
#include <state.h>


TEST(Automata, State_TwoDifferentStates_NotEqual){
    State state1(0);
    State state2(1);

    EXPECT_NE(state1, state2);
}