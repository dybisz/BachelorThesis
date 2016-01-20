//
// Created by jakub on 1/20/16.
//

#include <logger/log.h>
#include "classifier_constructor/classifier/serialization/fac_saver.h"

using namespace std;

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

FACSaver::FACSaver(const FAC *classifier,
                   string directoryPath, string dirName) {
    this->classifier = classifier;

    this->dirPath = directoryPath;
    this->dirName = dirName;
}

FACSaver::~FACSaver() {

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void FACSaver::save() {
    this->createMainDir();

    const vector<FACClassifier>& subClassifiers
            = classifier->getClassifiers();

    for(unsigned int i = 0; i < subClassifiers.size(); i++){
        FACClassifier subClassifier = subClassifiers[i];

    }

    //std::ofstream stateCorrFile;
    //stateCorrFile.open(logger::makePath(fullPath,"test.sc"));
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void FACSaver::createMainDir(){
    vector<string> toPath{dirPath, dirName};
    dirFullPath = logger::makePath(toPath);

    logger::makeDir(dirFullPath);
}

void FACSaver::saveSubClassifier(const FACClassifier& subClassifier, int id) {
    string name = to_string(id);
    string path = logger::makePath(dirFullPath, name);

    logger::makeDir(path);
}

void FACSaver::saveDFA(const DFA &dfa, std::string path) {

}

void FACSaver::saveStateCorrespondence(
        const StateCorrespondence &stateCorrespondence, std::string path) {

}
