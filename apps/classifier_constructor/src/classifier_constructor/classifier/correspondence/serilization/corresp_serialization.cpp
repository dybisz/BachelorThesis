//
// Created by jakub on 1/21/16.
//

#include <sstream>
#include <fstream>
#include <logger/log.h>
#include <string_utils.h>
#include <stdexcept>
#include "classifier_constructor/classifier/correspondence/serialization/corresp_serialization.h"

using namespace std;

namespace corresp_serialization {

string saveCorrespondenceToString(
        const Correspondence& correspondence) {
    string entireCorrespondenceString = "";
    const vector<Label>& labels = correspondence.getLabels();

    for(unsigned int i = 0; i < labels.size(); i++){
        stringstream ss;
        Label label = labels[i];
        ss << label.getValue() << SYMBOL_SEPERATOR;
        const vector<State>& states = correspondence.getStates(label);
        for(unsigned int j = 0; j < states.size(); j++){
            ss << states[j].getVal() << SYMBOL_SEPERATOR;
        }
        string correspondenceRowString = ss.str();
        // remove the last SYMBOL_SEPERATOR
        correspondenceRowString.pop_back();

        entireCorrespondenceString += correspondenceRowString;
        if(i != labels.size() - 1)
            entireCorrespondenceString += ROW_SEPERATOR;
    }
    return entireCorrespondenceString;
}

void saveCorrespondenceToFile(
        const Correspondence &correspondence, std::string dirPath,
        std::string fileName) {
    std::string dfaString = saveCorrespondenceToString(correspondence);

    fileName += CORRESPONDENCE_FILE_EXTENSION;

    std::ofstream file;
    std::string fullPath = logger::makePath(dirPath, fileName);
    file.open(fullPath);

    file << dfaString;

    file.close();
}

Correspondence loadCorrespondenceFromString(
        std::string correspondenceString) {
    Correspondence correspondence;
    vector<string> rows =
            str_util::splitString(correspondenceString, ROW_SEPERATOR);
    for(unsigned int i = 0; i < rows.size(); i++){
        vector<string> symbols =
                str_util::splitString(rows[i], SYMBOL_SEPERATOR);
        int labelValue = stoi(symbols[0]);
        Label label(labelValue);

        for(unsigned int j = 1; j < symbols.size(); j++){
            int stateValue = stoi(symbols[j]);
            State state(stateValue);
            correspondence.addCorrespondence(label, state);
        }
    }
    return correspondence;
}

Correspondence loadCorrespondenceFromFile(string filePath) {
    ifstream file;
    file.open(filePath);

    stringstream ss;
    if(!file.is_open()){
        throw invalid_argument("File not found" + filePath);
    }

    string str;
    getline(file, str);

    file.close();

    Correspondence correspondence = loadCorrespondenceFromString(str);

    return correspondence;
}
}