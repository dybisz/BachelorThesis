//
// Created by jakub on 1/21/16.
//

#ifndef BACHELOR_THESIS_CORRESP_SERIALIZATION_H
#define BACHELOR_THESIS_CORRESP_SERIALIZATION_H

#include <string>
#include <classifier_constructor/classifier/correspondence/correspondence.h>

/*
 * Correspondence contains states and its corresponding labels.
 * Let Correspondence c have the following correspondece:
 *
 *      l1 to s1, s2
 *      l2 to s3
 *      l3 to s4, s5
 *
 * Then the string that will save the object will look as follows:
 *      1,1,2;2,3;3,4,5
 * The first symbol in each row represents the lebel, rest are the
 * the corresponding states. The symbol values
 * are the private keyValues of states and labels
 */
namespace corresp_serialization {

    const std::string CORRESPONDENCE_FILE_EXTENSION = ".cpd";
    const std::string SYMBOL_SEPERATOR = ",";
    const std::string ROW_SEPERATOR = ";";

    /*
     * Saves the correspondence in string
     */
    std::string saveCorrespondenceToString(
            const Correspondence& correspondence);

    /*
     * Saves the correspondence to a file with fileName stored in
     * dirPath
     */
    void saveCorrespondenceToFile(
            const Correspondence& correspondence,
            std::string dirPath, std::string fileName);

    /*
     * Loads correspondence from string
     */
    Correspondence loadCorrespondenceFromString(
            std::string correspondenceString);

    Correspondence loadCorrespondenceFromFile(
            std::string filePath);
}

#endif //BACHELOR_THESIS_CORRESP_SERIALIZATION_H
