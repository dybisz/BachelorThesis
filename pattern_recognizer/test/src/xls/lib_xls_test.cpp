//
// Tests use example.xls file, so relative path to this file must be specified.
// For convenience, I present content of this simple file:
//
//     A    B   C
// 1 | 4    5   6
// 2 | 1    2   3
// 2 | 4    2   3
//
// Created by dybisz on 17.12.15.
//

#include <gtest/gtest.h>
//#include <debug_new.h>
#include "ExcelFormat.h"

using namespace std;
using namespace ExcelFormat;

const char* FILE_PATH = "./src/xls/example.xls";

/**
 * Opens file located under FILE_PATH.
 * Test checks whether file has been open
 * and reading variables works correctly.
 */
TEST(LibXlsTest, Open_XLS_File){

}

