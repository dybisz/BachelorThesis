//
// Created by jakub on 1/25/16.
//

#ifndef BACHELOR_THESIS_COMMON_H_H
#define BACHELOR_THESIS_COMMON_H_H

#include <xls_loader.h>
#include <transformation/transformation.h>

namespace experiments{
    XlsLoader getNativeXLSLoader();
    XlsLoader getForeignXLSLoader();

    transformation::TransformedLanguages getLanguages(
            XlsLoader& nativeXLSLoader,
            XlsLoader& foreignXLSLoader);
}

#endif //BACHELOR_THESIS_COMMON_H_H
