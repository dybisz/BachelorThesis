//
// Created by jakub on 1/7/16.
//

#include "dfa_fitness_updater.h"
#include <pso/particle_decoder_t.h>
#include <automata/dfa.h>

using namespace pso;

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

DFAFitnessUpdater::DFAFitnessUpdater(
                                ParticleShPtr_ConstVectorShPtr particles,
                                const ParticleDecoder_T* particleDecoder,
                                std::vector<Language*>* nativeLanguages,
                                std::vector<Language*>* foreignLanguages) :
                FitnessUpdater(particles, particleDecoder){
    this->nativeLanguages = nativeLanguages;
    this->foreignLanguages = foreignLanguages;
}

DFAFitnessUpdater::~DFAFitnessUpdater() {

}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void DFAFitnessUpdater::update(int startIndex, int finishIndex) {
    for(int i = startIndex; i <= finishIndex; i++){
        Particle_T& p = *((*particles)[i]);
        double fitnessValue = this->fitnessValue(p);
        p.setFitness(fitnessValue);
    }
}

//-----------------------------------------------------------//
//  PROTECTED METHODS
//-----------------------------------------------------------//

double DFAFitnessUpdater::fitnessValue(const Particle_T& p){
    int nativeSize = nativeLanguages->size();
    int foreignSize = foreignLanguages->size();

    double correctCount = 0;
    double countAll = 0;

    DFA* dfa = (DFA*)this->particleDecoder->decodeCurrent(p);

    for(int i = 0; i < nativeSize; i++){
        Language* language = (*nativeLanguages)[i];
        for(int w = 0; w < language->size(); w++){
            Word* word = language->getWord(w);
            unsigned int stateInt = dfa->compute(*word);
            State* s = new State(stateInt);
            if(language->isCorrespondingState(s)){
                correctCount++;
            }
            countAll++;

            delete s;
        }
    }

    for(int i = 0; i < foreignSize; i++){
        Language* language = (*foreignLanguages)[i];
        for(int w = 0; w < language->size(); w++){
            Word* word = language->getWord(w);
            unsigned int stateInt = dfa->compute(*word);
            State* s = new State(stateInt);
            if(language->isCorrespondingState(s)){
                correctCount++;
            }
            countAll++;

            delete s;
        }
    }

    delete dfa;

    double val = correctCount / countAll;
    return val;
}