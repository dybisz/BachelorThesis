//
// Created by dybisz on 17.12.15.
//

#include <xls_loader.h>

/* ---------------------------- */
/* ----- STATIC VARIABLES ----- */
/* ---------------------------- */
const int XlsLoader::ALL_ENTRIES = 0;

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

XlsLoader::XlsLoader() { }

XlsLoader::XlsLoader(string url, int numberOfLabels, int numberOfClasses) {
    try {
        loadDataFromFile(url, numberOfLabels, numberOfClasses);
    }
    catch (exception &e) {
        throw std::invalid_argument(e.what());
    }
}

XlsLoader::~XlsLoader() {
    for (auto iter = _loadedClasses.begin();
         iter != _loadedClasses.end(); ++iter) {
        delete (*iter);
    }
}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

void XlsLoader::loadDataFromFile(string url, int numberOfLabels,
                                 int numberOfClasses) {
    BasicExcel xls(url.c_str());
    XLSFormatManager fmt_mgr(xls);
    BasicExcelWorksheet *sheet = xls.GetWorksheet(0);
    CellFormat fmt_general(fmt_mgr);
    fmt_general.set_format_string("0.00000");

    if (sheet) {
        _loadFeaturesVectorsToClass(sheet, numberOfLabels, numberOfClasses);
    } else {
        throw invalid_argument("ExcelFormat cannot open sheet");
    }
}

vector<Class *> *XlsLoader::getClasses() {
    return &_loadedClasses;
}

string XlsLoader::printLabels() {
    string out = "Loaded labels: ";
    for (auto iter = _loadedClasses.begin();
         iter != _loadedClasses.end(); ++iter) {
        out += to_string((*iter)->getLabel());
        out += ",";
    }
    out += "\n";
    return out;
}

/* --------------------- */
/* ----- AUXILIARY ----- */
/* --------------------- */
string XlsLoader::toString() {
    string out = "";
    for (auto iter = _loadedClasses.begin();
         iter != _loadedClasses.end(); ++iter) {
        out += " ";
        out += (*iter)->toString();
    }
    return out;
}


void XlsLoader::_loadFeaturesVectorsToClass(BasicExcelWorksheet *pSheet,
                                              int numLabels,
                                              int numPatterns) {
    const int startRow = 2;
    const int labelCol = 0;

    int iterRow = startRow;

    while (_cellIsNotEmpty(iterRow, labelCol, pSheet)) {
        BasicExcelCell *cell = pSheet->Cell(iterRow, labelCol);
        int label = cell->GetDouble();

        // Check loading constraints
        if (_classInBoundaries(label, iterRow, numLabels, numPatterns)) {
            _addClassWithLabel(label);
            _addFeatureVectorToClass(label, iterRow, labelCol + 1, pSheet);
        }

        iterRow++;
    }
}

bool XlsLoader::_cellIsNotEmpty(const int row, const int col,
                                BasicExcelWorksheet *pSheet) {
    int type = pSheet->Cell(row, col)->Type();
    return !(type == 0); // 0 <=> empty cell
}

void XlsLoader::_addClassWithLabel(int label) {

    // Check if pattern with provided label already
    // exists in loaded patterns.
    for (auto iter = _loadedClasses.begin();
         iter != _loadedClasses.end(); ++iter) {
        if ((*iter)->getLabel() == label) {
            return;
        }
    }

    // If not, add new one with this label
    Class *pattern = new Class(label);
    _loadedClasses.push_back(pattern);

}

void XlsLoader::_addFeatureVectorToClass(int label, int row, const int col,
                                           BasicExcelWorksheet *pSheet) {
    FeaturesVector *fv = new FeaturesVector();
    int iterCol = col;

    while (_cellIsNotEmpty(row, iterCol, pSheet)) {
        BasicExcelCell *cell = pSheet->Cell(row, iterCol);
        double value = cell->GetDouble();
        (*fv) + value;
        iterCol++;
    }

    Class *pattern = _getClassWithLabel(label);
    pattern->appendFeatureVector(fv);
}

Class *XlsLoader::_getClassWithLabel(int label) {
    for (auto iter = _loadedClasses.begin();
         iter != _loadedClasses.end(); ++iter) {
        if ((*iter)->getLabel() == label) {
            return (*iter);
        }
    }

    return NULL;
}

bool XlsLoader::_classInBoundaries(int label, int row, int numLabels,
                                     int numPatterns) {
    // Pattern numbering
//    int pattern = row - ((label * (numPatterns)) + 2);
    Class* patt = _getClassWithLabel(label);
    bool labelDecision = true;
    bool patternDecision = true;

    if (numLabels != ALL_ENTRIES) {
        labelDecision = (label < numLabels);
    }

    if (numPatterns != ALL_ENTRIES && patt != NULL) {
        patternDecision = (patt->size() < numPatterns);
    }

    return labelDecision && patternDecision;
}
