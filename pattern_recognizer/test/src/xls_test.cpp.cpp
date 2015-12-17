//
// Created by dybisz on 17.12.15.
//

#include <gtest/gtest.h>
#include "libxl.h"

using namespace libxl;

TEST(XLSTest, Include_Test){
    int x = 20;
    EXPECT_EQ(20, x);
}