//
// Created by jakub on 1/7/16.
//

#include <gtest/gtest.h>

#include <logger/log.h>

int main(int argc, char **argv) {
    std::cout << "Starting Unit Tests" << std::endl;
    logger::initLog();

    ::testing::InitGoogleTest(&argc, argv);

    int ret = RUN_ALL_TESTS();

    logger::closeLog();

    return ret;
}