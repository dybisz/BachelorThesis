//
// Created by dybisz on 21.12.15.
//

#include <gtest/gtest.h>
#include <state.h>


TEST(StateTest, Constructor_From_Integer) {
    State* s1 = new State(1);
    EXPECT_EQ(1, (*s1).getVal());
    delete s1;
}

TEST(StateTest, Constructor_From_Symbol) {
    State * s1 = new State(1);
    State * s2 = new State(*s1);
    EXPECT_EQ(*s1, *s2);
    delete s1;
    delete s2;
}

TEST(StateTest, Equality_Symbol_Operator) {
    State* s1 = new State(1);
    EXPECT_EQ((*s1), 1);
    delete s1;
}

TEST(StateTest, Equality_Integer_Operator) {
    State * s1 = new State(1);
    State * s2 = new State(1);
    EXPECT_EQ(*s1, *s2);
    delete s1;
    delete s2;
}

TEST(StateTest, State_TwoDifferentStates_NotEqual){
    State state1(0);
    State state2(1);

    EXPECT_NE(state1, state2);
}