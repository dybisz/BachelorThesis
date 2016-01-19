//
// Created by jakub on 1/19/16.
//


#include <gtest/gtest.h>
#include <console/flag.h>
#include <console/flag_reader.h>
#include <classifier_constructor/settings/app_settings.h>
#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_constructor/settings/log_settings.h>
#include <classifier_constructor/settings/thread_settings.h>
#include <classifier_constructor/settings/pso_settings.h>

TEST(Console, NoFlagsHaveTheSameShortValue) {
    console::clearFlags();

    settings::setAppFlags();
    settings::setClassifierFlags();
    settings::setLogFlags();
    settings::setPSOFlags();
    settings::setThreadFlags();

    std::vector<console::Flag> flags = console::getFlags();
    unsigned int size = flags.size();
    for (unsigned int i = 0; i < size - 1; i++) {
        for (unsigned int j = i + 1; j < size; j++) {
            console::Flag flag1 = flags[i];
            console::Flag flag2 = flags[j];

            EXPECT_NE(flag1.short_f, flag2.short_f);
        }
    }
}

TEST(Console, NoFlagsHaveTheSameLongValue) {
    console::clearFlags();

    settings::setAppFlags();
    settings::setClassifierFlags();
    settings::setLogFlags();
    settings::setPSOFlags();
    settings::setThreadFlags();

    std::vector<console::Flag> flags = console::getFlags();
    unsigned int size = flags.size();
    for (unsigned int i = 0; i < size - 1; i++) {
        for (unsigned int j = i + 1; j < size; j++) {
            console::Flag flag1 = flags[i];
            console::Flag flag2 = flags[j];

            EXPECT_NE(flag1.long_f, flag2.long_f);
        }
    }
}