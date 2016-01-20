//
// Created by jakub on 12/4/15.
//

#include "dfa_serialization.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string_utils.h>
#include <logger/log.h>

namespace dfa_serialization
{
    std::string saveDFAToString(const DFA& dfa){
        std::string SEPERATOR = ",";
        std::stringstream ss;
        int stateCount = dfa.getStateCount();
        int symbolCount = dfa.getSymbolCount();

        ss << stateCount << SEPERATOR << symbolCount << SEPERATOR;

        const TransitionFunction* tf = dfa.getTransitionFunction();
        for(unsigned int state = 0; state < stateCount; state++){
            for(unsigned int symbol = 0; symbol < symbolCount; symbol++){
                int toState = tf->getState(state, symbol);
                // Unified form starts indexing from 1
                toState += 1;

                ss << toState << SEPERATOR;
            }
        }
        std::string dfaString = ss.str();
        // Remove the last empty seperator
        dfaString.pop_back();

        return dfaString;
    }

    void saveDFAToFile(const DFA& dfa,
                       std::string filepath, std::string name){
        std::string dfaString = saveDFAToString(dfa);

        name += DFA_EXTENSION;

        std::ofstream dfaFile;
        std::string fullPath = logger::makePath(filepath, name);
        dfaFile.open(fullPath);

        dfaFile << dfaString;
    }


    DFA* loadDFAFromFile(std::string dfaURL) {
        ifstream file;
        file.open(dfaURL);

        stringstream ss;
        if(!file.is_open()){
            throw std::invalid_argument("File not found" + dfaURL);
        }

        std::string str;
        std::getline(file, str);

        file.close();

        DFA* dfa = loadDFAFromString(str);

        return dfa;
    }

    DFA* loadDFAFromString(std::string dfaUnifiedForm){
        std::vector<std::string> entries_str =
                str_util::splitString(dfaUnifiedForm,",");

        unsigned int stateCount = stoi(entries_str[0]);
        unsigned int symbolCount = stoi(entries_str[1]);

        unsigned int len = stateCount*symbolCount;

        if(entries_str.size() != (len + 2)){
            std::cout << entries_str.size() << std::endl;
            std::cout << "Length: " << len << std::endl;
            throw std::invalid_argument("Wrong content in : " + dfaUnifiedForm);
        }

        TransitionFunction* tf = new TransitionFunction(stateCount,
                                                        symbolCount);

        unsigned int currentState = 0;
        unsigned int currentSymbol = 0;
        unsigned int counter = 0;

        while(currentState < stateCount){
            currentSymbol = 0;
            while(currentSymbol < symbolCount){
                // We start from counter + 2 since we read 2 first entries
                unsigned int toState = stoi(entries_str[(counter++) + 2]);

                // toState - 1, We index states from 0
                tf->addTransition(currentState, currentSymbol, toState-1);

                currentSymbol++;
            }
            currentState++;
        }

        DFA* dfa = new DFA(tf);

        return dfa;
    }
}