//
// Created by dybisz on 17.12.15.
//

#include <gtest/gtest.h>
#include "word.h"
#include <symbol.h>

using namespace std;

TEST(WordTest, Constructor_Empty) {
    int symbols[3] = {1, 4, 2};
    Word *fv = new Word();
    // It should be empty ..
    EXPECT_EQ(0, fv->size());
    // .. end return exception when accesing any of elements
    ASSERT_ANY_THROW((*fv)(0));
    ASSERT_ANY_THROW((*fv)[0]);
    delete fv;
}

TEST(WordTest, Constructor_From_Integer_Array) {
    int symbols[3] = {1, 4, 2};
    Word *fv = new Word(symbols, 3);
    EXPECT_EQ(symbols[0], ((*fv)(0)));
    EXPECT_EQ(symbols[1], ((*fv)(1)));
    EXPECT_EQ(symbols[2], ((*fv)(2)));
    delete fv;
}

TEST(WordTest, Constructor_From_Symbols) {
    Symbol s1(1);
    Symbol s2(4);
    Symbol s3(2);
    vector<Symbol> entries = {s1, s2, s3};
    Word *fv = new Word(entries);
    EXPECT_EQ(s1, *((*fv)[0]));
    EXPECT_EQ(s2, *((*fv)[1]));
    EXPECT_EQ(s3, *((*fv)[2]));
    delete fv;
}

TEST(WordTest, Constructor_From_Symbols_Pointers) {
    Symbol *s1 = new Symbol(1);
    Symbol *s2 = new Symbol(4);
    Symbol *s3 = new Symbol(2);
    vector<Symbol *> entries = {s1, s2, s3};
    Word *fv = new Word(entries);
    EXPECT_EQ(*s1, *((*fv)[0]));
    EXPECT_EQ(*s2, *((*fv)[1]));
    EXPECT_EQ(*s3, *((*fv)[2]));
    delete fv;
}

TEST(WordTest, Get_Value_Operator) {
    vector<int> entries = {1, 4, 2};
    Word *fv = new Word(entries);
    EXPECT_EQ(1, (*fv)(0));
    EXPECT_EQ(4, (*fv)(1));
    EXPECT_EQ(2, (*fv)(2));
    delete fv;
}

TEST(WordTest, Get_Symbol_Pointer_Operator) {
    Word *fv = new Word();
    (*fv) + 1;
    (*fv) + 4;
    (*fv) + 2;
    Symbol *s1 = new Symbol(1);
    Symbol *s2 = new Symbol(4);
    Symbol *s3 = new Symbol(2);
    EXPECT_EQ(*s1, *((*fv)[0]));
    EXPECT_EQ(*s2, *((*fv)[1]));
    EXPECT_EQ(*s3, *((*fv)[2]));
    delete s1;
    delete s2;
    delete s3;
    delete fv;
}

TEST(WordTest, Add_Integer_Operator) {
    Word *fv = new Word();
    Symbol *s1 = new Symbol(1);
    Symbol *s2 = new Symbol(4);
    Symbol *s3 = new Symbol(2);
    (*fv) + s1;
    (*fv) + s2;
    (*fv) + s3;
    EXPECT_EQ(1, (*fv)(0));
    EXPECT_EQ(4, (*fv)(1));
    EXPECT_EQ(2, (*fv)(2));
    EXPECT_EQ(*s1, *((*fv)[0]));
    EXPECT_EQ(*s2, *((*fv)[1]));
    EXPECT_EQ(*s3, *((*fv)[2]));
    delete fv;
}

TEST(WordTest, Add_Symbol_Operator) {
    Word *fv = new Word();
    (*fv) + 1;
    (*fv) + 4;
    (*fv) + 2;
    EXPECT_EQ(1, (*fv)(0));
    EXPECT_EQ(4, (*fv)(1));
    EXPECT_EQ(2, (*fv)(2));
    delete fv;
}

TEST(WordTest, Equal_Operator) {
    Word *fv1 = new Word();
    (*fv1) + 1;
    (*fv1) + 4;
    (*fv1) + 2;

    Symbol s1(1);
    Symbol s2(4);
    Symbol s3(2);
    vector<Symbol> entries = {s1, s2, s3};
    Word *fv2 = new Word(entries);

    EXPECT_EQ((*fv1), (*fv1));
    EXPECT_EQ((*fv2), (*fv2));
    EXPECT_EQ((*fv1), (*fv2));

    delete fv1;
    delete fv2;
}