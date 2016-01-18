//
// Created by dybisz on 17.12.15.
//

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "xls_loader.h"

using namespace std;

string DATA_PATH = "./res/short_Natives.xls";

#include <string>
#include <limits.h>
#include <unistd.h>


TEST(XlsLoaderTest, Read_Data){

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL)
        fprintf(stdout, "Current working dir: %s\n", cwd);

    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH);
    delete xlsLoader;
}

TEST(XlsLoaderTest, Read_Specified_Num_Of_Labels) {
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH, 1);
    vector<Pattern*> loadedPatterns = *(xlsLoader->getPatterns());
    EXPECT_EQ(1, loadedPatterns.size());
    delete xlsLoader;
}

TEST(XlsLoaderTest, Read_Specified_Num_Of_Patterns) {
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH, XlsLoader::ALL_ENTRIES, 5);
    vector<Pattern*> loadedPatterns = *(xlsLoader->getPatterns());
    EXPECT_EQ(2, loadedPatterns.size());
    EXPECT_EQ(5, loadedPatterns[0]->size());
    delete xlsLoader;
}

TEST(XlsLoaderTest, Read_Specified_Num_Of_Labels_And_Patterns) {
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH, 1, 50);
    vector<Pattern*> loadedPatterns = *(xlsLoader->getPatterns());
    EXPECT_EQ(50, loadedPatterns[0]->size());
    delete xlsLoader;
}