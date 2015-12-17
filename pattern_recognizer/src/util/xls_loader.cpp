//
// Created by dybisz on 17.12.15.
//

#include <xls_loader.h>

XlsLoader::XlsLoader() { }

XlsLoader::XlsLoader(string url) {
    setUrl(url);
    loadDataFromFile();
}

void XlsLoader::setUrl(string url){
    this->_url = url.c_str();
}

void XlsLoader::loadDataFromFile() {
    Book* book = xlCreateBook();
    if(book) {
        if (book->load(_url)) {
            _processSheet(book->getSheet(0));
        }
        book->release();
    }
}

void XlsLoader::_processSheet(ISheetT<char> *pSheet) {
    if (pSheet) {
//                double d = sheet->readNum(0, 0);
//                d = sheet->readNum(1, 0);
    }
}
