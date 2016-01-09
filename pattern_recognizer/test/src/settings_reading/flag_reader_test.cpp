//
// Created by jakub on 12/29/15.
//



#include <gtest/gtest.h>
#include <settings_reading/flag_reader_t.h>


TEST(FlagReader, Activate){
    int someSetting = 5;

    auto activate = [](int* value, std::string argument){
        *value = std::atoi(argument.c_str());
    };

    FlagReader_T<int> flagReaderT(
                &someSetting,
                activate,
                "-x", "--xx");

    int expectedValue = 10;
    flagReaderT.apply("10");

    int actualValue = someSetting;

    EXPECT_EQ(expectedValue, actualValue);
}