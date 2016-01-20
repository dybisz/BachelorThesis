//
// Created by jakub on 12/4/15.
//

#include <gtest/gtest.h>
#include <iostream>
#include <fstream>
#include <string_utils.h>
#include <automata/transition/transition_function.h>
#include <automata/dfa.h>
#include <dfa_serialization.h>

//-----------------------------------------------------------//
//  DECLARATIONS
//-----------------------------------------------------------//


//-----------------------------------------------------------//
//  DEFINITIONS
//-----------------------------------------------------------//


//-----------------------------------------------------------//
//  TESTS
//-----------------------------------------------------------//


TEST(DFASerialization_DFASaver,
    DFASavedToString_LoadedFromString_TransitionMatches){
    int stateCount = 4;
    int symbolCount = 2;

    TransitionFunction* tf = new TransitionFunction(stateCount, symbolCount);
    tf->addTransition(0,0,1);
    tf->addTransition(1,0,2);
    tf->addTransition(2,0,2);
    tf->addTransition(3,0,3);

    tf->addTransition(0,1,3);
    tf->addTransition(1,1,2);
    tf->addTransition(2,1,2);
    tf->addTransition(3,1,3);

    DFA dfa(tf);

    std::string dfaString = dfa_serialization::saveDFAToString(dfa);

    dfa_serialization::saveDFAToFile(dfa, ".", "fac");

    DFA* loadedDFA = dfa_serialization::loadDFAFromString(dfaString);
    const TransitionFunction* loadedTF = loadedDFA->getTransitionFunction();

    EXPECT_EQ(1, loadedTF->getState(0, 0));
    EXPECT_EQ(2, loadedTF->getState(1, 0));
    EXPECT_EQ(2, loadedTF->getState(2, 0));
    EXPECT_EQ(3, loadedTF->getState(3, 0));

    EXPECT_EQ(3, loadedTF->getState(0, 1));
    EXPECT_EQ(2, loadedTF->getState(1, 1));
    EXPECT_EQ(2, loadedTF->getState(2, 1));
    EXPECT_EQ(3, loadedTF->getState(3, 1));
}

TEST(DFASerialization_DFALoader, ReadFile_ProperStateCount) {
    const char* filename = "tmpfile.txt";
    std::ofstream outFile;
    // Create tmp file
    outFile.open(filename );

    if(outFile.is_open()){
        // append example dfa
        outFile << "4,2,2,4,3,3,3,3,4,4";
    }
    outFile.close();

    std::ifstream inFile;
    inFile.open(filename);

    if(inFile.is_open())
    {
        std::string str;
        std::getline(inFile, str);

        std::vector<std::string> entries_str = str_util::splitString(str,",");

        unsigned int stateCount = stoi(entries_str[0]);
        unsigned int symbolCount = stoi(entries_str[1]);

        unsigned int expectedStateCount = 4;
        unsigned int expectedSymbolCount = 2;

        EXPECT_EQ(expectedStateCount, stateCount);
        EXPECT_EQ(expectedSymbolCount, symbolCount);

        inFile.close();
    }
    std::remove(filename);
}

TEST(DFASerialization_DFALoader, ReadFile_ProperTransition) {
    const char* filename = "tmpfile.txt";
    std::ofstream outFile;
    // Create tmp file
    outFile.open(filename );

    if(outFile.is_open()){
        // append example dfa
        outFile << "4,2,2,4,3,3,3,3,4,4";
    }
    outFile.close();

    std::ifstream inFile;
    inFile.open(filename);

    if(inFile.is_open())
    {
        std::string str;
        std::getline(inFile, str);

        std::vector<std::string> entries_str = str_util::splitString(str,",");

        unsigned int stateCount = stoi(entries_str[0]);
        unsigned int symbolCount = stoi(entries_str[1]);

        TransitionFunction tf(stateCount, symbolCount);

        unsigned int currentState = 0;
        unsigned int currentSymbol = 0;
        unsigned int counter = 0;

        while(currentState < stateCount){
            currentSymbol = 0;
            while(currentSymbol < symbolCount){
                // We start from counter + 2 since we read 2 first entries
                unsigned int toState = stoi(entries_str[(counter++) + 2]);

                // toState - 1, We index states from 0
                tf.addTransition(currentState, currentSymbol, toState-1);

                currentSymbol++;
            }
            currentState++;
        }

        EXPECT_EQ(1, tf.getState(0, 0));
        EXPECT_EQ(2, tf.getState(1, 0));
        EXPECT_EQ(2, tf.getState(2, 0));
        EXPECT_EQ(3, tf.getState(3, 0));

        EXPECT_EQ(3, tf.getState(0, 1));
        EXPECT_EQ(2, tf.getState(1, 1));
        EXPECT_EQ(2, tf.getState(2, 1));
        EXPECT_EQ(3, tf.getState(3, 1));

        inFile.close();
    }
    std::remove(filename);
}