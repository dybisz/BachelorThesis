//
// Created by jakub on 1/17/16.
//

#include "transformation_precision.h"



namespace quality {

    double computeTransformationPrecision(std::vector<Language*>* languages){
        int intersectionSize = 0;
        int unionSize = 0;

        unsigned int languageCount = languages->size();
        std::vector<Word*> alreadyProcessedWords;

        for(unsigned int i = 0; i < languageCount - 1; i++){
            Language* language1 = (*languages)[i];
            for(unsigned int j = i + 1; j < languageCount; j++){
                Language* language2 = (*languages)[j];

            }
        }
    }

}