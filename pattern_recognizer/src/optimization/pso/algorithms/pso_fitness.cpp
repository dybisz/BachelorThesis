//
// Created by jakub on 12/1/15.
//

#include "pso_fitness.h"
#include <error.h>
#include <algorithm>
#include <relation_induced.h>

namespace pso
{
    namespace fitness
    {
        void* initFitness(void *argv)
        {
            thread_args* t_args = (thread_args*)argv;

            /*          Critical section           */
            if (pthread_mutex_lock(t_args->mutex) != 0)
                ERR("pthread_mutex_lock");

            // Get data to calculate interval
            int id                              = t_args->id;
            int thread_count                    = t_args->thread_count;
            vector<Particle*>* particles        = t_args->particles;

            int particleCount                   = (*particles).size();

            // Check if it is divided evenly
            int reminder = particleCount % thread_count;

            // Give every  thread its unique interval
            int sub_count = particleCount / thread_count;
            int start   = id * sub_count;
            int finish  = start + sub_count - 1;

            // Add indices not given yet to the last thread.
            if(id == thread_count - 1)
                finish += reminder;

            /*          End of Critical section           */
            pthread_mutex_unlock(t_args->mutex);

            calculatePBestAndFitness(start, finish, t_args);

            return NULL;
        }

        void calculatePBestAndFitness(int start, int finish,
                                      thread_args* t_args)
        {
            vector<Particle*>* particles = t_args->particles;

            // Start main loop
            for (int i = start; i <= finish; i++) {

                Particle* p = (*particles)[i];

                p->setFitness(fitnessValue(p,
                                           t_args->nativeLanguages,
                                           t_args->foreignLanguages));

                // Check if particle is in new pbest
                if (p->getBestFitness() < p->getFitness()) {
                    p->saveCurrentConfigAsBest();
                }

                /*          Critical section           */
                if (pthread_mutex_lock(t_args->mutex) != 0)
                    ERR("pthread_mutex_lock");

                // Update global best fitness value
                calculateGBestFitness(p, t_args->bestParticles,
                                      t_args->globalBestFitness);

                /*          End of Critical section           */
                pthread_mutex_unlock(t_args->mutex);
            }
        }

        double fitnessValue(Particle *p,
                            std::vector<Language*>* nativeLanguages,
                            std::vector<Language*>* foreignLanguages)
        {
            int nativeSize = nativeLanguages->size();
            int foreignSize = foreignLanguages->size();

            double correctCount = 0;
            double countAll = 0;

            const DFA* dfa = p->getCurrentDFA();


            for(int i = 0; i < nativeSize; i++){
                Language* language = (*nativeLanguages)[i];
                for(int w = 0; w < language->size(); w++){
                    Word* word = language->getWord(w);
                    std::vector<int> entries;
                    for(int j = 0; j < word->size(); j++){
                        int value = word->getSymbol(j)->getVal();
                        value--;
                        entries.push_back(value);
                    }
                    Word hackedWord(entries);

                    unsigned int stateInt = dfa->compute(hackedWord);
                    State* s = new State(stateInt);
                    if(language->isCorrespondingStatePtr(s)){
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
                    std::vector<int> entries;
                    for(int j = 0; j < word->size(); j++){
                        int value = word->getSymbol(j)->getVal();
                        value--;
                        entries.push_back(value);
                    }
                    Word hackedWord(entries);

                    unsigned int stateInt = dfa->compute(hackedWord);
                    State* s = new State(stateInt);
                    if(language->isCorrespondingStatePtr(s)){
                        correctCount++;
                    }
                    countAll++;

                    delete s;
                }
            }
            double val = correctCount / countAll;
            //std::cout << "correctCount: " << correctCount << std::endl;
            //std::cout << "countAll: " << countAll << std::endl;
            //std::cout << "Val: " << val << std::endl;
            return val;
        }

        void calculateGBestFitness(Particle* particle,
                                   std::vector<Particle*>* bestParticles,
                                   double* globalBestFitness)
        {

            double currentFitness = particle->getFitness();

            // Check if another particle has global fitness
            if (*globalBestFitness == currentFitness) {
                // If that particle is not already here
                if (std::find(bestParticles->begin(), bestParticles->end(),
                              particle) == bestParticles->end()) {
                    bestParticles->push_back(particle);
                }
            }

            else if (*globalBestFitness < currentFitness) {
                bestParticles->clear();

                *globalBestFitness = currentFitness;

                bestParticles->push_back(particle);
            }
        }
    }
}