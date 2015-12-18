//
// Created by dybisz on 18.12.15.
//
#include <gtest/gtest.h>
#include <symbol.h>

TEST(SymbolTest, Constructor_From_Integer) {
    Symbol* s1 = new Symbol(1);
    EXPECT_EQ(1, (*s1).getVal());
    delete s1;
}

TEST(SymbolTest, Constructor_From_Symbol) {
    Symbol * s1 = new Symbol(1);
    Symbol * s2 = new Symbol(*s1);
    EXPECT_EQ(*s1, *s2);
    delete s1;
    delete s2;
}

TEST(SymbolTest, Equality_Symbol_Operator) {
    Symbol* s1 = new Symbol(1);
    EXPECT_EQ((*s1), 1);
    delete s1;
}

TEST(SymbolTest, Equality_Integer_Operator) {
    Symbol * s1 = new Symbol(1);
    Symbol * s2 = new Symbol(1);
    EXPECT_EQ(*s1, *s2);
    delete s1;
    delete s2;
}

