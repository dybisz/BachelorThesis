//
// Created by jakub on 1/20/16.
//

#include <logger/log.h>
#include <dfa_serialization.h>
#include "classifier_constructor/classifier/serialization/fac_saver.h"

using namespace std;

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

FACSaver::FACSaver(const CFAC *classifier,
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

    const vector<FAC>& subClassifiers
            = classifier->getClassifiers();

    for(unsigned int i = 0; i < subClassifiers.size(); i++){
        FAC subClassifier = subClassifiers[i];
        string dirName = "classifier_" + to_string(i);
        saveSubClassifier(subClassifier, dirName);
    }
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

void FACSaver::createMainDir(){
    vector<string> toPath{dirPath, dirName};
    dirFullPath = logger::makePath(toPath);

    logger::makeDir(dirFullPath);
}

void FACSaver::saveSubClassifier(const FAC& subClassifier,
                                 string dirName) {
    string path = logger::makePath(dirFullPath, dirName);
    logger::makeDir(path);

    const DFA& dfa = subClassifier.getDFA();
    const std::vector<Correspondence>& stateCorrespondenceVector
            = subClassifier.getCorrespondence();

    string dfaName = DEFAULT_DFA_NAME;
    saveDFA(dfa, path, dfaName);

    string stateCorrespodenceName = DEFAULT_STATE_CORRES_NAME;
    saveStateCorrespondenceVector(stateCorrespondenceVector,
                            path, stateCorrespodenceName);
}

void FACSaver::saveDFA(const DFA &dfa,
                       string path, string name) {
    dfa_serialization::saveDFAToFile(dfa, path, name);
}

void FACSaver::saveStateCorrespondenceVector(
        const std::vector<Correspondence>& stateCorrespondenceVector,
        string path,
        string name) {
    name += STATE_CORRES_EXT;
    std::ofstream stateCorrFile;
    string fullPath = logger::makePath(path, name);
    stateCorrFile.open(fullPath);

    stateCorrFile.close();
}
