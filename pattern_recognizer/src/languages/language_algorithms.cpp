//
// Created by jakub on 12/27/15.
//

#include "language_algorithms.h"

namespace languages
{
    /*
     * Selects state correspondence of native and foreign languages
     */
    void selectStateCorrespondence(std::vector<Language*>* nativeLanguages,
                                   std::vector<Language*>* foreignLanguages,
                                   unsigned int statesPerNative,
                                   unsigned int statesPerForeign){
        int nativeSize = nativeLanguages->size();
        int foreignSize = foreignLanguages->size();

        int currentStateKey = 0;

        for(int i = 0; i < nativeSize; i++){
            std::vector<State> states;
            for(int j = 0; j < statesPerNative; j++){
                State state(currentStateKey);
                states.push_back(state);

                currentStateKey++;
            }
            (*nativeLanguages)[i]->setStates(states);
        }

        std::vector<State> states;
        for(int i = 0; i < statesPerForeign; i++){
            State state(currentStateKey);
            states.push_back(state);

            currentStateKey++;
        }
        for(int i = 0; i < foreignSize; i++){
            (*foreignLanguages)[i]->setStates(states);
        }
    }
}
