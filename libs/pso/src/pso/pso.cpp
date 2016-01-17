//
// Created by jakub on 12/29/15.
//

#include <pso/pso.h>
#include <pso/fitness_updater.h>
#include <pso/neighbourhood_updater.h>
#include <pso/particle_updater.h>
#include <pso/particle_decoder.h>

#include <math/random.h>
#include <time/clock.h>


using namespace std;

namespace pso {

//-----------------------------------------------------------//
//  CONSTRUCTORS
//-----------------------------------------------------------//

PSO::PSO(ParticleShPtr_ConstVectorShPtr particles,
                FitnessUpdater* fitnessUpdater,
                NeighbourhoodUpdater* neighUpdater,
                ParticleUpdater* particleUpdater,
                int maxIterations,
                unsigned int threadCount):
        fitnessUpdater(fitnessUpdater),
        neighUpdater(neighUpdater),
        particleUpdater(particleUpdater),
        maxIterations(maxIterations),
        threadCount(threadCount),
        globalBestParticle(*((*particles)[0])){
    this->particles = particles;
    swarmSize = particles->size();
}

PSO::~PSO() {
    delete fitnessUpdater;
    delete neighUpdater;
    delete particleUpdater;
}

//-----------------------------------------------------------//
//  PUBLIC METHODS
//-----------------------------------------------------------//

void PSO::start() {
    threading::ThreadPool threadPool(threadCount);

    // Create structure for thread arguments
    thread_argv* targs = new thread_argv[threadCount];

    // Pointer to initial function
    void* (*fun_ptr)(void*);
    fun_ptr = &startParallelPSO;

    int curr_iter = 0;
    bool do_work = true;

    int reminder = this->swarmSize % threadPool.size();
    int sub_count = this->swarmSize / threadPool.size();

    // Initialize the structure with data
    for(unsigned int i = 0; i < threadCount; i++){

        int start = i * sub_count;
        int finish = start + sub_count - 1;
        if (i == threadCount - 1)
            finish += reminder;

        targs[i].startIndex = start;
        targs[i].finishIndex = finish;

        targs[i].tid = i;
        targs[i].pso = this;
        targs[i].curr_iter = &curr_iter;
        targs[i].do_work = &do_work;

        targs[i].threadPool = &threadPool;

        threadPool.createThread(fun_ptr, (&targs[i]));
    }

    threadPool.joinAll();
}
const Particle *PSO::getBestParticle() const{
    return &globalBestParticle;
}

const PSOObject*PSO::getBestPSOObject() const {
    PSOObject* psoObject =
            this->getDecoder().decodePBest((*this->getBestParticle()));

    return psoObject;
}

const ParticleDecoder &PSO::getDecoder() const {
    return this->fitnessUpdater->getParticleDecoder();
}

//-----------------------------------------------------------//
//  PRIVATE METHODS
//-----------------------------------------------------------//

bool PSO::hasConvereged(const int* iter){
    return (*iter >= this->maxIterations);
}

bool PSO::updateBestParticle(){
    bool hasChanged = false;

    if(bestParticle == NULL) {
        bestParticle = (*particles)[0];
    }

    for(unsigned int i = 0; i < swarmSize; i++){
        if((*particles)[i]->getBestFitness() > bestParticle->getBestFitness()){
            bestParticle = (*particles)[i];
            hasChanged = true;
        }
    }

    if(bestParticle->getBestFitness() >= globalBestParticle.getBestFitness()) {
        globalBestParticle = *bestParticle;
    }

    return hasChanged;
}


void PSO::resetParticles() {
    for(unsigned int i = 0; i < particles->size(); i++){
        ParticleShPtr particle = (*particles)[i];

        double posIntervalMin = particle->getPosIntervalMin();
        double posIntervalMax = particle->getPosIntervalMax();

        double velIntervalMin = particle->getVelIntervalMin();
        double velIntervalMax = particle->getVelIntervalMax();

        int particleDimension = particle->getPosition().size();

        Point<double> position(particleDimension);
        Point<double> velocity(particleDimension);

        for(unsigned int j = 0; j < particleDimension; j++){
            position[j] = rnd::generateRandomNumber(posIntervalMin,
                                                      posIntervalMax);
            velocity[j] = rnd::generateRandomNumber(velIntervalMin,
                                                      velIntervalMax);
        }

        particle->setPosition(position);
        particle->setVelocity(velocity);

        particle->setPbest(position);
        particle->setLbest(position);

        particle->setBestFitness(0);

    }
}

void PSO::printInfo(double fitnessUpdateTime,
                      double neighbourhoodUpdateTime,
                      double particleUpdateTime,
                      double overallTime,
                      double averageTimeOfIteration,
                      double ETA,
                      int currentIteration,
                      int& numberOfLinesToReset) {
    // Clean previous entry
    for (int i = 0; i < numberOfLinesToReset; i++) {
        cout << "\e[A\r";
    }

    numberOfLinesToReset = 0;
    string prefix = "          ";
    string prefixIcons = "               ";
    cout << endl;
    numberOfLinesToReset++;

    cout << prefixIcons << " ___  ___  ___" << endl;
    cout << prefixIcons << "| _ \\/ __|/ _ \\" << endl;
    cout << prefixIcons << "|  _/\\__ \\ (_) |" << endl;
    cout << prefixIcons << "|_|  |___/\\___/" << endl;
    cout << prefixIcons << "                    " << endl;
    numberOfLinesToReset += 5;

    cout << prefix << "[Iteration              ]: "
        << currentIteration << "/" << this->maxIterations << endl;
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Swarm Size             ]: "
    << this->swarmSize << endl;
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Overall Time           ]: "
    << overallTime << endl;
    numberOfLinesToReset++;

    cout << prefix << "[ETA Time               ]: "
    << ETA << endl;
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Avg Iter Time          ]: "
    << averageTimeOfIteration << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Last Fitness Time      ]: "
        << fitnessUpdateTime << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Last Neigh Time        ]: "
    << neighbourhoodUpdateTime << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Last Particle Time     ]: "
    << particleUpdateTime << endl;
    numberOfLinesToReset++;

    cout << endl;
    numberOfLinesToReset++;

    double bestFitness = 0;
    if (bestParticle != NULL) {
        bestFitness = bestParticle->getBestFitness();
    }
    cout << prefix << "[Best Fitness Cur Gen   ]: "
        << bestFitness << endl;
    numberOfLinesToReset++;

    cout << prefix << "[Best Fitness All Gen   ]: "
    << globalBestParticle.getBestFitness() << endl;
    numberOfLinesToReset++;

    cout << prefix << "" << endl;
    cout << prefix << "            .-. " << endl;
    cout << prefix << "           o   \\     .-." << endl;
    cout << prefix << "               .----.\'   \\" << endl;
    cout << prefix << "              .\'o)  / `.   o" << endl;
    cout << prefix << "             /         |" << endl;
    cout << prefix << "             \\_)       /-." << endl;
    cout << prefix << "              \'_.`    \\  \\" << endl;
    cout << prefix << "               `.      |  \\" << endl;
    cout << prefix << "               |       \\ |" << endl;
    cout << prefix << "           .--/`-.     / /" << endl;
    cout << prefix << "          .'.-/`-. `.  .\\|" << endl;
    cout << prefix << "         /.' /`._ `-    '-." << endl;
    cout << prefix << "    ____(|__/`-..`-   '-._ \\" << endl;
    cout << prefix << "   |`------.'-._ `      ||\\ \\" << endl;
    cout << prefix << "   || #   /-.   `   /   || \\|" << endl;
    cout << prefix << "   ||   #/   `--'  /  /_::_|)__" << endl;
    cout << prefix << "   `|____|-._.-`  /  ||`--------`" << endl;
    cout << prefix << "         \\-.___.` | / || #      |" << endl;
    cout << prefix << "          \\       | | ||   #  # |" << endl;
    cout << prefix << "          /`.___.'\\ |.`|________|" << endl;
    cout << prefix << "          | /`.__.'|'.`" << endl;
    cout << prefix << "        __/ \\    __/ \\" << endl;
    cout << prefix << "       /__.-.)  /__.-.)" << endl;
    cout << prefix << endl << endl;
    numberOfLinesToReset += 26;
}

//-----------------------------------------------------------//
//  FRIEND METHODS
//-----------------------------------------------------------//

void *startParallelPSO(void *argv) {
    thread_argv *targs = (thread_argv *) argv;

    PSO * pso = targs->pso;
    bool* do_work = targs->do_work;
    int* curr_iter = targs->curr_iter;
    unsigned int tid = targs->tid;
    threading::ThreadPool *threadPool = targs->threadPool;

    threadPool->lockAll();

    threadPool->unlockAll();

    threadPool->synchronizeAll();

    if (tid == threading::T_BOSS) {
        *do_work = true;
        *curr_iter = 0;
    }

    threadPool->synchronizeAll();

    int numberOfLines = 0;

    double fitnessTime = 0;
    double neighTime = 0;
    double updateTime = 0;
    double overallTime = 0;
    double averageTimeOfIteration = 0;
    double ETA = 0;

    int noFitnessUpdateInARowCount = 0;
    int noFitnessUpdateInARowCountBeforeReset = 59;

    while (*do_work) {
        if (tid == threading::T_BOSS) {
            overallTime += fitnessTime + neighTime + updateTime;
            if(*curr_iter != 0)
                averageTimeOfIteration = overallTime / *curr_iter;
            ETA = averageTimeOfIteration * (pso->maxIterations - (*curr_iter));
            pso->printInfo(fitnessTime,
                           neighTime,
                           updateTime,
                           overallTime,
                           averageTimeOfIteration,
                           ETA,
                           *curr_iter, numberOfLines);
        }

        threadPool->synchronizeAll();

        if(tid == threading::T_BOSS)
            clk::startClock();
        pso->fitnessUpdater->update(targs->startIndex,
                                    targs->finishIndex);
        if(tid == threading::T_BOSS)
            fitnessTime = clk::stopClock();

        threadPool->synchronizeAll();

        bool newBestParticleUpdated = true;
        if(tid == threading::T_BOSS) {
            newBestParticleUpdated = pso->updateBestParticle();
            if(!newBestParticleUpdated)
                noFitnessUpdateInARowCount++;
            else
                noFitnessUpdateInARowCount = 0;
        }

        threadPool->synchronizeAll();

        if (tid == threading::T_BOSS) {
            clk::startClock();
            if(!newBestParticleUpdated)
                pso->neighUpdater->update();
            neighTime = clk::stopClock();
        }

        threadPool->synchronizeAll();

        if(tid == threading::T_BOSS)
            clk::startClock();
        pso->particleUpdater->update(targs->startIndex,
                                     targs->finishIndex);
        if(tid == threading::T_BOSS)
            updateTime = clk::stopClock();

        threadPool->synchronizeAll();

        if (tid == threading::T_BOSS) {
            *do_work = !pso->hasConvereged(curr_iter);
            *curr_iter += 1;

            if(noFitnessUpdateInARowCount >=
                    noFitnessUpdateInARowCountBeforeReset) {
                pso->resetParticles();
                noFitnessUpdateInARowCount = 0;
            }
        }

        threadPool->synchronizeAll();
    }
    return NULL;
}
}
