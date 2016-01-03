//
// Created by dybisz on 17.12.15.
//

#ifndef BACHELOR_THESIS_XLS_LOADER_H
#define BACHELOR_THESIS_XLS_LOADER_H

#include <string>
#include <iostream>
#include <vector>
#include <pattern.h>
#include "ExcelFormat.h"
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

    void setUrl(string url);
    void loadDataFromFile(string url, int i, int i1);

    vector<Pattern *> *getPatterns();
    string printLabels();
    string toString();

private:
    // Relative path to a data file.
    // Type: const char*, because of libxls demands.
    const char *_url;
    vector<Pattern *> _loadedPatterns;

    void _addPatternWithLabel(int label);

    Pattern *_getPatternWithLabel(int label);

    // One needs to know that appropriate format of loading files looks as
    // follows:
    // [EMPTY ROW]
    // [FEATURES NUMBERING WHERE 0 COLUMN CONTAINS LABELS]
    // [LABEL][FEATURES VALUES]
    // [LABEL][FEATURES VALUES]
    // ...
    // [LABEL][FEATURES VALUES]
    //
    // WARNING: Labels must be grouped together, no mixing!
    //
    // Methods will automatically detect resolution of the table so there
    // is no need to provide sizes - just stick to the format.
    bool _cellIsNotEmpty(const int row, const int col,
                         BasicExcelWorksheet *pSheet);

    void _loadFeaturesVectorsToPatterns(BasicExcelWorksheet *pSheet,
                                        int numberOfLabels,
                                        int numberOfPatterns);

    void _addFeatureVectorToPattern(int label, int row, const int col,
                                    BasicExcelWorksheet *pSheet);


    bool _patternInBoundaries(int label, int row, int numLabels, int numPatterns);
};

#endif //BACHELOR_THESIS_XLS_LOADER_H
