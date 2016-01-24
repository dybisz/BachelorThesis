//
// Created by dybisz on 19.12.15.
//

#include <gtest/gtest.h>
#include "class.h"

using namespace std;

TEST(PatternTest, Pattern_Init) {
    vector<double> v1 = {1.2, 2.6, 3.01};
    vector<double> v2 = {5.2, 4.1, 9.4};
    vector<double> v3 = {1.4, 8.1, 8.8};
    FeaturesVector *fv1 = new FeaturesVector(v1);
    FeaturesVector *fv2 = new FeaturesVector(v2);
    FeaturesVector *fv3 = new FeaturesVector(v3);
    vector<FeaturesVector *> *features = new vector<FeaturesVector*>({fv1, fv2, fv3});

    Class *pattern = new Class(features, 0);
    EXPECT_EQ(3, pattern->size());
    delete pattern;
}

TEST(PatternTest, Get_Value_Operator) {
    vector<double> v1 = {1.2, 2.6, 3.01};
    vector<double> v2 = {5.2, 4.1, 9.4};
    vector<double> v3 = {1.4, 8.1, 8.8};
    FeaturesVector *fv1 = new FeaturesVector(v1);
    FeaturesVector *fv2 = new FeaturesVector(v2);
    FeaturesVector *fv3 = new FeaturesVector(v3);
    vector<FeaturesVector *> *features = new vector<FeaturesVector*>({fv1, fv2, fv3});

    Class *pattern = new Class(features, 0);
    double e1 = (*(*pattern)[0])[0];
    double e2 = (*(*pattern)[0])[2];
    double e3 = (*(*pattern)[1])[2];
    double e4 = (*(*pattern)[2])[2];

    EXPECT_EQ(1.2, e1);
    EXPECT_EQ(3.01, e2);
    EXPECT_EQ(9.4, e3);
    EXPECT_EQ(8.8, e4);

    ASSERT_ANY_THROW((*pattern)[4]);

    delete pattern;
}