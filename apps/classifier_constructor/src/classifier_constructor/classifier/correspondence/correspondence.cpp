//
// Created by jakub on 1/20/16.
//

#include <algorithm>
#include <stdexcept>
#include <classifier_constructor/classifier/correspondence/correspondence.h>

using namespace std;

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

Correspondence::Correspondence(){
}


Correspondence::Correspondence(const Correspondence &correspondence) {
    for(unsigned int i = 0; i < correspondence.labels.size();i++){
        this->labels.push_back(correspondence.labels[i]);
    }
    for(unsigned int i = 0; i < correspondence.correspondingStates.size();i++){
        const vector<State>& states = correspondence.correspondingStates[i];
        vector<State> myStates;
        for(unsigned int j = 0; j < states.size(); j++){
            myStates.push_back(states[j]);
        }
        this->correspondingStates.push_back(myStates);
    }
}


//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

const std::vector<Label> &Correspondence::getLabels() const{
    return labels;
}

const std::vector<State>&Correspondence::getStates(
        const Label& label) const {
    int labelIndex = this->getLabelIndex(label);
    if (labelIndex == LABEL_NOT_FOUND){
        throw invalid_argument("No such label in correspondence");
    }
    return correspondingStates[labelIndex];
}


bool Correspondence::isCorresponding(const Label& label,
                                     const State& state) const{
    int labelIndex = this->getLabelIndex(label);
    if (labelIndex == LABEL_NOT_FOUND) return false;

    vector<State> states = correspondingStates[labelIndex];
    for(unsigned int i = 0; i < states.size(); i++){
        if (state  == states[i])
            return true;
    }
    return false;
}

void Correspondence::addCorrespondence(Label label, State state) {
    int labelIndex = this->getLabelIndex(label);
    if (labelIndex == LABEL_NOT_FOUND) {
        addNewCorrespondence(label, state);
    }else{
        addStateToExistingCorrespondence(state, labelIndex);
    }
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

int Correspondence::getLabelIndex(const Label& label) const{
    vector<Label>::const_iterator it;

    it = find(labels.begin(), labels.end(), label);

    int index = distance(labels.begin(), it);

    return (it != labels.end() ? index : LABEL_NOT_FOUND);
}

void Correspondence::addNewCorrespondence(Label label, State state) {
    labels.push_back(label);

    vector<State> states;
    states.push_back(state);
    correspondingStates.push_back(states);
}

void Correspondence::addStateToExistingCorrespondence(State state,
                                                      int labelIndex) {
    bool alreadyExists = false;
    for(unsigned int i = 0 ; i < correspondingStates[labelIndex].size(); i++){
        if(correspondingStates[labelIndex][i] == state) {
            alreadyExists = true;
            break;
        }
    }
    if(!alreadyExists)
        correspondingStates[labelIndex].push_back(state);
}

//-----------------------------------------------------------//
//  OPERATORS
//-----------------------------------------------------------//

Correspondence &Correspondence::operator=(const Correspondence &other) {
    for(unsigned int i = 0; i < other.labels.size();i++){
        this->labels.push_back(other.labels[i]);
    }
    for(unsigned int i = 0; i < other.correspondingStates.size();i++){
        const vector<State>& states = other.correspondingStates[i];
        vector<State> myStates;
        for(unsigned int j = 0; j < states.size(); j++){
            myStates.push_back(states[j]);
        }
        this->correspondingStates.push_back(myStates);
    }
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Correspondence &c) {
    for(unsigned int i = 0; i < c.labels.size(); i++){
        Label label = c.labels[i];
        os << "Label(" << to_string(label.getValue()) << ") : ";
        vector<State> states = c.correspondingStates[i];
        for(unsigned int j = 0; j < states.size(); j++){
            os << to_string(states[j].getVal());
            if(j != states.size())
                os << ", ";
        }
        os << "\n";
    }
    return os;
}
