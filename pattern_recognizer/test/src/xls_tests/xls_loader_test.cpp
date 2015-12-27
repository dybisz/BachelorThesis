//
// Created by dybisz on 17.12.15.
//

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include "xls_loader.h"
//#include <debug_new.h>

using namespace std;

string DATA_PATH = "./res/Natives.xls";

// not much to testing for now
TEST(XlsLoaderTest, Read_Data){
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH);

    delete xlsLoader;
}

