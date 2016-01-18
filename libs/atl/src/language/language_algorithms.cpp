//
// Created by jakub on 12/27/15.
//

#include <language/language_algorithms.h>

namespace language
{
    void selectStateCorrespondence(std::vector<Language*>* nativeLanguages,
                                   std::vector<Language*>* foreignLanguages,
                                   unsigned int statesPerNative,
                                   unsigned int statesPerForeign){
        int nativeSize = nativeLanguages->size();
        int foreignSize = foreignLanguages->size();

        int currentStateKey = 0;
        // Native
        for(int i = 0; i < nativeSize; i++){
            std::vector<State*>* states = new std::vector<State*>;
            for(int j = 0; j < statesPerNative; j++){
                State* state = new State(currentStateKey);
                states->push_back(state);
                currentStateKey++;
            }
            (*nativeLanguages)[i]->setStates(*states);
        }
        // Foreign
        for(int f = 0; f < foreignSize; f++) {
            std::vector<State*>* states = new std::vector<State*>;
            int foreignStartStateKey = currentStateKey;
            for (int i = 0; i < statesPerForeign; i++) {
                State *state = new State(foreignStartStateKey );
                states->push_back(state);

                foreignStartStateKey++;
            }
            (*foreignLanguages)[f]->setStates(*states);
        }
    }

    int numberOfOccurrences(const vector<Word*>& words,
                            const Word& word) {
        int occurenceCounter = 0;

        for(unsigned int i = 0; i < words.size(); i++){
            Word* currentWord = words[i];
            if (*currentWord == word){
                occurenceCounter++;
            }
        }

        return occurenceCounter;
    }

}
