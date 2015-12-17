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
#include <string>
#include "libxl.h"


using namespace std;
using namespace libxl;

const char* FILE_PATH = "./src/xls/example.xls";

/**
 * Opens file located under FILE_PATH.
 * Test checks whether file has been open
 * and reading variables works correctly.
 */

TEST(XLSTest, Open_XLS_File){
    Book* book = xlCreateBook();
    int hasBeenOpened = -1;

    if(book) {
        if (book->load(FILE_PATH)) {
            Sheet *sheet = book->getSheet(0);
            if (sheet) {
                double d = sheet->readNum(0, 0);
                EXPECT_EQ(4, d);
                d = sheet->readNum(0, 1);
                EXPECT_EQ(5, d);
                d = sheet->readNum(2, 2);
                EXPECT_EQ(3, d);
                d = sheet->readNum(1, 0);
                EXPECT_EQ(1, d);
                hasBeenOpened++;
            }
        }
        book->release();
    }
    EXPECT_EQ(0, hasBeenOpened);
}

TEST(XLSTest, FIKIMIKI){
    Book* book = xlCreateBook();
    if(book) {
        if (book->load(FILE_PATH)) {
            Sheet *sheet = book->getSheet(0);
            if (sheet) {
                CellType d = sheet->cellType(50, 0);
                if(d != CELLTYPE_EMPTY)
                    cout << d << endl;
            }
        }
        book->release();
    }
}
