//
// Created by jakub on 12/22/15.
//

#include "classification_exp.h"

#include <loaders/xls_loader.h>
#include <settings/global_settings.h>
#include <logger/log.h>

namespace experiments
{
    void runClassificationExperiment(){
        logger::log("Starting Classification Experiment");

        // Note: if xlsLoader goes out of scope, patterns are deleted.
        XlsLoader nativeXLSLoader(global_settings::NATIVE_XLS_PATH);
        XlsLoader foreignXLSLoader(global_settings::FOREIGN_XLS_PATH);

        std::vector<Pattern*>* nativePatterns = nativeXLSLoader.getPatterns();
        std::vector<Pattern*>* foreignPatterns = foreignXLSLoader.getPatterns();

        classification::printLoadedPatternsInfo(nativePatterns, "Native");
        classification::printLoadedPatternsInfo(foreignPatterns, "Foreign");
    }

    namespace classification
    {
        void printLoadedPatternsInfo(std::vector<Pattern*>* patterns,
                                     std::string headerInfo){
            std::stringstream ss;
            ss << "Patterns. " << headerInfo << std::endl;
            ss << "Different Patterns count. "
                << patterns->size() << std::endl;

            int sum = 0;
            for(int i = 0; i < patterns->size(); i++){
                sum += (*patterns)[i]->size();
                ss << "Pattern["
                    << i
                    << "] count: "
                    << (*patterns)[i]->size() << std::endl;
            }
            ss << "All Patterns count: " << sum;

            logger::log(ss.str());
        }
    }
}