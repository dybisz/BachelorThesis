//
// Created by dybisz on 17.12.15.
//

#ifndef BACHELOR_THESIS_XLS_LOADER_H
#define BACHELOR_THESIS_XLS_LOADER_H

#include <string>
#include "libxl.h"

using namespace std;
using namespace libxl;

/**
 * Class loads data from provided .xls file.
 * All values are stored in patterns, each consisting of at least one
 * features vector.
 */
class XlsLoader {
public:
    // User can either provide the loader with path to .xls file,
    // or leave empty and supply it later. If supplied, data will be
    // automatically loaded, if not one needs to call appropriate method.
    XlsLoader();
    XlsLoader(string url);

    void setUrl(string url);
    void loadDataFromFile();

private:
    // Relative path to a data file.
    // Type: const char*, because of libxls demands.
    const char* _url;

    void _processSheet(ISheetT<char> *pSheet);
};

#endif //BACHELOR_THESIS_XLS_LOADER_H
