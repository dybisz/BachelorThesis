//
// Created by dybisz on 17.12.15.
//

#ifndef BACHELOR_THESIS_XLS_LOADER_H
#define BACHELOR_THESIS_XLS_LOADER_H

#include <string>
#include <iostream>
#include <vector>
#include "class.h"
#include <ExcelFormat.h>
#include <cstdlib>
#include <algorithm>

using namespace std;
using namespace ExcelFormat;

/**
 * Class loads data from provided .xls file.
 * All values are stored in patterns, each consisting of at least one
 * features vector.
 */
class XlsLoader {
public:
    // Used for making default values more transparent. It suggests class that
    // all entries should be loaded.
    static const int ALL_ENTRIES;


    // User can either provide the loader with path to .xls file,
    // or leave empty and supply it later. If supplied, data will be
    // automatically loaded, if not - one needs to call appropriate method.
    // What is more, user can provide number of classes to load along with
    // number of patterns. If those numbers are not provided, by default,
    // all entries will be loaded.
    // WARNING:
    XlsLoader();
    XlsLoader(string url,
              int numberOfLabels = ALL_ENTRIES,
              int numberOfPatterns = ALL_ENTRIES);
    ~XlsLoader();

    void loadDataFromFile(string url, int i, int i1);

    vector<Class *> *getClasses();
    string printLabels();
    string toString();

private:
    // Relative path to a data file.
    // Type: const char*, because of libxls demands.
    const char *_url;
    vector<Class *> _loadedClasses;

    void _addClassWithLabel(int label);

    Class *_getClassWithLabel(int label);

    // One needs to know that appropriate format of loading files looks as
    // follows:
    // [EMPTY ROW]
    // [FEATURES NUMBERING WHERE 0 COLUMN CONTAINS LABELS]
    // [LABEL][FEATURES VALUES]
    // [LABEL][FEATURES VALUES]
    // ...
    // [LABEL][FEATURES VALUES]
    //
    // Methods will automatically detect resolution of the table so there
    // is no need to provide sizes - just stick to the format.
    bool _cellIsNotEmpty(const int row, const int col,
                         BasicExcelWorksheet *pSheet);
    void _loadFeaturesVectorsToClass(BasicExcelWorksheet *pSheet,
                                       int numberOfLabels,
                                       int numberOfClasses);
    void _addFeatureVectorToClass(int label, int row, const int col,
                                    BasicExcelWorksheet *pSheet);
    bool _classInBoundaries(int label, int row, int numLabels,
                              int numPatterns);
};

#endif //BACHELOR_THESIS_XLS_LOADER_H
