//
// Created by dybisz on 17.12.15.
//

#include <gtest/gtest.h>
#include <feature_vector.h>
#include <symbol.h>

using namespace std;

TEST(FeatureVectorTest, Constructor_From_Symbols_Pointers) {
    Symbol* s1 = new Symbol(1);
    Symbol* s2 = new Symbol(4);
    Symbol* s3 = new Symbol(2);
    vector<Symbol*> entries = {s1, s2, s3};
    FeatureVector* fv = new FeatureVector(entries);
    EXPECT_EQ(*s1, *((*fv)[0]));
    EXPECT_EQ(*s2, *((*fv)[1]));
    EXPECT_EQ(*s3, *((*fv)[2]));
    delete fv;
}

TEST(FeatureVectorTest, Constructor_From_Symbols) {
    Symbol s1(1);
    Symbol s2(4);
    Symbol s3(2);
    vector<Symbol> entries = {s1, s2, s3};
    FeatureVector* fv = new FeatureVector(entries);
    EXPECT_EQ(s1, *((*fv)[0]));
    EXPECT_EQ(s2, *((*fv)[1]));
    EXPECT_EQ(s3, *((*fv)[2]));
    delete fv;
}

TEST(FeatureVectorTest, Get_Value_Operator) {
    vector<int> entries = {1, 4 ,2};
    FeatureVector* fv = new FeatureVector(entries);
    EXPECT_EQ(1, (*fv)(0));
    EXPECT_EQ(4, (*fv)(1));
    EXPECT_EQ(2, (*fv)(2));
    delete fv;
}

TEST(FeatureVectorTest, Get_Symbol_Pointer_Operator){
    FeatureVector* fv = new FeatureVector();
    (*fv) + 1;
    (*fv) + 4;
    (*fv) + 2;
    Symbol* s1 = new Symbol(1);
    Symbol* s2 = new Symbol(4);
    Symbol* s3 = new Symbol(2);
    EXPECT_EQ(*s1, *((*fv)[0]));
    EXPECT_EQ(*s2, *((*fv)[1]));
    EXPECT_EQ(*s3, *((*fv)[2]));
    delete s1;
    delete s2;
    delete s3;
    delete fv;
}

TEST(FeatureVectorTest, Add_Integer_Operator){
    FeatureVector* fv = new FeatureVector();
    Symbol* s1 = new Symbol(1);
    Symbol* s2 = new Symbol(4);
    Symbol* s3 = new Symbol(2);
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

TEST(FeatureVectorTest, Add_Symbol_Operator){
    FeatureVector* fv = new FeatureVector();
    (*fv) + 1;
    (*fv) + 4;
    (*fv) + 2;
    EXPECT_EQ(1, (*fv)(0));
    EXPECT_EQ(4, (*fv)(1));
    EXPECT_EQ(2, (*fv)(2));
    delete fv;
}

TEST(FeatureVectorTest, Equal_Operator){
    FeatureVector* fv1 = new FeatureVector();
    (*fv1) + 1;
    (*fv1) + 4;
    (*fv1) + 2;

    Symbol s1(1);
    Symbol s2(4);
    Symbol s3(2);
    vector<Symbol> entries = {s1, s2, s3};
    FeatureVector* fv2 = new FeatureVector(entries);

    EXPECT_EQ((*fv1), (*fv1));
    EXPECT_EQ((*fv2), (*fv2));
    EXPECT_EQ((*fv1), (*fv2));

    delete fv1;
    delete fv2;
}