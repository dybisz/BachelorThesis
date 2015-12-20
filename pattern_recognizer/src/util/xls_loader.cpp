//
// Created by dybisz on 17.12.15.
//

#include <xls_loader.h>
#include <logger.h>
#include <state.h>

/* ------------------------------------ */
/* ----- CONSTRUCTORS/DESTRUCTORS ----- */
/* ------------------------------------ */

XlsLoader::XlsLoader() { }

XlsLoader::XlsLoader(string url) {
    try {
        setUrl(url);
        loadDataFromFile(url);
    }
    catch (exception &e) {
        LOG_ERROR(e.what());
    }
}

XlsLoader::~XlsLoader() {
    for (auto iter = _loadedPatterns.begin();
         iter != _loadedPatterns.end(); ++iter) {
        delete (*iter);
    }
}

/* ------------------------- */
/* ----- PUBLIC/VITAL ------ */
/* ------------------------- */

void XlsLoader::setUrl(string url) {
    this->_url = url.c_str();
}

void XlsLoader::loadDataFromFile(string url) {
    BasicExcel xls(_url);
    XLSFormatManager fmt_mgr(xls);
    BasicExcelWorksheet *sheet = xls.GetWorksheet(0);
    CellFormat fmt_general(fmt_mgr);
    fmt_general.set_format_string("0.00000");

    if (sheet) {
        _processSheet(sheet);
    } else {
        throw invalid_argument("ExcelFormat cannot open sheet");
    }
}

vector<Pattern *> *XlsLoader::getPatterns() {
    return &_loadedPatterns;
}

string XlsLoader::printLabels() {
    string out = "Loaded labels: ";
    for (auto iter = _loadedPatterns.begin();
         iter != _loadedPatterns.end(); ++iter) {
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
    int a = 0;
    for (auto iter = _loadedPatterns.begin();
         iter != _loadedPatterns.end(); ++iter) {
        out += " ";
        out += (*iter)->toString();
    }
    return out;
}

void XlsLoader::_processSheet(BasicExcelWorksheet *pSheet) {
    _loadFeaturesVectorsToPatterns(pSheet);
}

void XlsLoader::_loadFeaturesVectorsToPatterns(BasicExcelWorksheet *pSheet) {
    const int startRow = 2;
    const int labelCol = 0;

    int iterRow = startRow;

    while (_cellIsNotEmpty(iterRow, labelCol, pSheet)) {
        BasicExcelCell *cell = pSheet->Cell(iterRow, labelCol);
        int label = cell->GetDouble();
        _addPatternWithLabel(label);
        _addFeatureVectorToPattern(label, iterRow, labelCol + 1, pSheet);
        iterRow++;
    }
}

bool XlsLoader::_cellIsNotEmpty(const int row, const int col,
                                BasicExcelWorksheet *pSheet) {
    int type = pSheet->Cell(row, col)->Type();
    return !(type == 0); // 0 <=> empty cell
}

void XlsLoader::_addPatternWithLabel(int label) {

    // Check if pattern with provided label exists
    for (auto iter = _loadedPatterns.begin();
         iter != _loadedPatterns.end(); ++iter) {
        if ((*iter)->getLabel() == label) {
            return;
        }
    }

    // If not, add new one with this label
    Pattern *pattern = new Pattern(label);
    _loadedPatterns.push_back(pattern);

}

void XlsLoader::_addFeatureVectorToPattern(int label, int row, const int col,
                                           BasicExcelWorksheet *pSheet) {
    FeaturesVector *fv = new FeaturesVector();
    int iterCol = col;

    while (_cellIsNotEmpty(row, iterCol, pSheet)) {
        BasicExcelCell *cell = pSheet->Cell(row, iterCol);
        double value = cell->GetDouble();
        (*fv) + value;
        iterCol++;
    }

    Pattern *pattern = _getPatternWithLabel(label);
    pattern->appendFeatureVector(fv);
}

Pattern *XlsLoader::_getPatternWithLabel(int label) {
    for (auto iter = _loadedPatterns.begin();
         iter != _loadedPatterns.end(); ++iter) {
        if ((*iter)->getLabel() == label) {
            return (*iter);
        }
    }

    return NULL;
}
