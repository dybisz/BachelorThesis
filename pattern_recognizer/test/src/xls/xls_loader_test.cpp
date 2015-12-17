//
// Created by dybisz on 17.12.15.
//

#include <gtest/gtest.h>
#include <string>
#include "xls_loader.h"


using namespace std;

string DATA_PATH = "./src/xls/example.xls";

TEST(XlsLoaderTest, Read_Data){
    XlsLoader* xlsLoader = new XlsLoader(DATA_PATH);


    xlsLoader = NULL;
    delete xlsLoader;
}