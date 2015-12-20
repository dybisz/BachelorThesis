//
// Created by dybisz on 19.12.15.
//


#include <gtest/gtest.h>
#include <features_vector.h>
//#include <debug_new.h>
using namespace std;

TEST(FeatureVectorTest, Constructor_From_Doubles_Vector) {
    vector<double> entries = {1.0, 4.0, 2.0};
    FeaturesVector * fv = new FeaturesVector(entries);
    EXPECT_EQ(entries[0], (*fv)[0]);
    EXPECT_EQ(entries[1], (*fv)[1]);
    EXPECT_EQ(entries[2], (*fv)[2]);
    delete fv;
}

TEST(FeatureVectorTest, Add_Double_Operator){
    FeaturesVector * fv = new FeaturesVector();
    (*fv) + 1;
    (*fv) + 4;
    (*fv) + 2;
    EXPECT_EQ(1, (*fv)[0]);
    EXPECT_EQ(4, (*fv)[1]);
    EXPECT_EQ(2, (*fv)[2]);
    delete fv;
}

TEST(FeatureVectorTest, Equal_Operator){
    FeaturesVector * fv1 = new FeaturesVector();
    (*fv1) + 1;
    (*fv1) + 4;
    (*fv1) + 2;

    vector<double> entries = {1.0, 4.0, 2.0};
    FeaturesVector * fv2 = new FeaturesVector(entries);

    EXPECT_EQ((*fv1), (*fv1));
    EXPECT_EQ((*fv2), (*fv2));
    EXPECT_EQ((*fv1), (*fv2));

    delete fv1;
    delete fv2;
}