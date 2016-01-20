//
// Created by jakub on 12/22/15.
//

#include <classifier_constructor/experiments/classification_exp.h>

#include <classifier_constructor/transformation/transformation_analyzer.h>
#include <logger/log.h>
#include <patterns_to_languages.h>
#include <classifier_constructor/classification/classifier.h>

#include <classifier_constructor/pso_classifier/dfa_particle_decoder.h>

#include <pso/particle_factory.h>
#include <pso/neighbourhood_updaters/nb_star_topology.h>
#include <pso/particle_updaters/particle_updater_spherical.h>

#include <xls_loader.h>

#include <classifier_constructor/settings/thread_settings.h>
#include <classifier_constructor/settings/pso_settings.h>
#include <classifier_constructor/settings/log_settings.h>
#include <classifier_constructor/settings/classifier_settings.h>
#include <classifier_constructor/settings/app_settings.h>
#include <classifier_constructor/settings/transformation_settings.h>

using namespace pso;
using namespace transformation;

namespace experiments {

    void runTransformationAnalysis(){
        logger::log("Starting Transformation Analysis");

        logger::log("Loading Patterns");
        XlsLoader nativeXLSLoader(settings::NATIVE_XLS_PATH);
        XlsLoader foreignXLSLoader(settings::FOREIGN_XLS_PATH);

        std::vector<Pattern *> *nativePatterns = nativeXLSLoader.getPatterns();
        std::vector<Pattern *> *foreignPatterns = foreignXLSLoader.getPatterns();

        logger::log("Starting Transformation Analysis");

        TransformationAnalyzer transformationAnalyzer
        (
            nativePatterns,
            settings::MIN_ALHPABET_SIZE,
            settings::MAX_ALHPABET_SIZE
        );

        transformationAnalyzer.runAnalysis();

        logger::log("Printing Results");

        transformationAnalyzer.printResults();
    }

    void runClassifierConstructor() {
        logger::log("Starting PSO Experiment");

        logger::log("Loading Patterns");

        if (settings::NATIVE_XLS_PATH == ""){
            logger::log("Please Provide NATIVE_XLS_PATH");
            return ;
        }

        // Note: if xlsLoader goes out of scope, patterns are deleted.
        XlsLoader nativeXLSLoader(settings::NATIVE_XLS_PATH, 1, 900);
        XlsLoader foreignXLSLoader(settings::FOREIGN_XLS_PATH, 1, 900);

        std::vector<Pattern *> *nativePatterns = nativeXLSLoader.getPatterns();
        std::vector<Pattern *> *foreignPatterns = foreignXLSLoader.getPatterns();

        classification::printLoadedPatternsInfo(nativePatterns, "NATIVE");
        classification::printLoadedPatternsInfo(foreignPatterns, "FOREIGN");

        /* Transformation */
        logger::log("Language Transformation");

        std::vector<Language *> *nativeLanguages =
                patterns_to_languages::convert(nativePatterns,
                                               settings::ALPHABET_SIZE);

        std::vector<Language *> *foreignLanguages =
                patterns_to_languages::convert(foreignPatterns,
                                               settings::ALPHABET_SIZE);


        int nativeSize = nativeLanguages->size();
        int numberOfStates = nativeSize * settings::STATES_PER_NATIVE +
                             settings::STATES_PER_FOREIGN;

        int particleDimension = numberOfStates * settings::ALPHABET_SIZE;
        ParticleFactory particleFactory =
                classification::createParticleFactory(
                        settings::SWARM_SIZE, particleDimension,
                        settings::ENCODING_DELTA,
                        numberOfStates + settings::ENCODING_DELTA
                        - settings::UPPER_BOUND_ERR,
                        (double)-numberOfStates, (double)numberOfStates,
                        settings::MAX_VELOCITY
                );
        /*
        std::stringstream ss;
        ss << "Creating Particles" << std::endl;
        ss << "Count:          " << swarmSize << std::endl;
        ss << "Dimensions:     " << particleDimension << std::endl;

        ss << "posIntervalMin: " << posIntervalMin << std::endl;
        ss << "posIntervalMax: " << posIntervalMax << std::endl;

        ss << "velIntervalMin: " << velIntervalMin << std::endl;
        ss << "velIntervalMax: " << velIntervalMax << std::endl;

        ss << "maxVelocity:    " << maxVelocity << std::endl;

        logger::log(ss.str());
         */
        ParticleShPtr_ConstVectorShPtr particles =
                particleFactory.createUnifromParticles();

        ParticleDecoder * particleDecoder =
                classification::createParticleDecoder(numberOfStates,
                                            settings::ALPHABET_SIZE,
                                            settings::ENCODING_DELTA);

        FitnessUpdater* fitnessUpdater =
                classification::createFitnessUpdater(particles,
                particleDecoder,nativeLanguages, foreignLanguages);
        int numberOfInformants = 3;
        NeighbourhoodUpdater* neighbourhoodUpdater =
                classification::createNeighbourhoodUpdater(
                        particles, numberOfInformants);

        int numberOfTries = 1;

        ParticleUpdater* particleUpdater =
                classification::createPaticleUpdater(particles,
                              settings::LEARNING_FACTOR,
                              settings::PARTICLE_VEL_WEIGHT,
                              numberOfTries);

        PSO * pso =
                classification::createPSO(particles, fitnessUpdater,
                                          neighbourhoodUpdater,
                                          particleUpdater,
                                          settings::MAX_ITER,
                                          settings::TRUE_THREAD_COUNT);

        Classifier *classifier = new Classifier(
                pso,
                nativeLanguages,
                foreignLanguages,
                settings::STATES_PER_NATIVE,
                settings::STATES_PER_FOREIGN,
                settings::ALPHABET_SIZE,
                settings::TESTING_SET_RATIO);

        classifier->runClassification();

        delete classifier;
    }

    namespace classification {
        PSO * getPSOForExperiments(){

        }

        pso::PSO * createPSO(ParticleShPtr_ConstVectorShPtr particles,
                             pso::FitnessUpdater* fitnessUpdater,
                             pso::NeighbourhoodUpdater* neighUpdater,
                             pso::ParticleUpdater* particleUpdater,
                             int maxIterations, int threadCount){
            pso::PSO * pso = new PSO(particles,
                                          fitnessUpdater,
                                          neighUpdater,
                                          particleUpdater,
                                          maxIterations,
                                          threadCount);

            return pso;
        }

        pso::ParticleFactory createParticleFactory(int swarmSize,
                                                        int particleDimension,
                                                        double posIntervalMin,
                                                        double posIntervalMax,
                                                        double velIntervalMin,
                                                        double velIntervalMax,
                                                        double maxVelocity ){
            pso::ParticleFactory particleFactory(
                    swarmSize, particleDimension,
                    posIntervalMin, posIntervalMax,
                    velIntervalMin, velIntervalMax,
                    maxVelocity
            );

            return particleFactory;
        }

        pso::ParticleDecoder * createParticleDecoder(int numberOfStates,
                                                     int numberOfSymbols,
                                                     double encodingDelta){
            pso::ParticleDecoder * particleDecoder = new DFAParticleDecoder(
                    numberOfStates, numberOfSymbols,
                    encodingDelta
            );

            return particleDecoder;
        }

        pso::NeighbourhoodUpdater* createNeighbourhoodUpdater(
                                ParticleShPtr_ConstVectorShPtr particles,
                                int numberOfParticlesToInform ){
            pso::NeighbourhoodUpdater* neighbourhoodUpdater
                    = new pso::NBStarTopology(
                            particles, numberOfParticlesToInform
                    );

            return neighbourhoodUpdater;
        }

        pso::FitnessUpdater* createFitnessUpdater(
                                ParticleShPtr_ConstVectorShPtr particles,
                                pso::ParticleDecoder * particleDecoder,
                                std::vector<Language*>* nativeLanguages,
                                std::vector<Language*>* foreignLanguages){
            pso::FitnessUpdater* fitnessUpdater = new DFAFitnessUpdater(
                    particles, particleDecoder,
                    nativeLanguages, foreignLanguages
            );

            return fitnessUpdater;
        }

        pso::ParticleUpdater* createPaticleUpdater(
                            ParticleShPtr_ConstVectorShPtr particles,
                            double learningFactor, double velocityWeight,
                            int timesToAttemptPointGenerationWithinHyperSphere){
            pso::ParticleUpdater* particleUpdater = new
                    pso::ParticleUpdaterSpherical(particles,
                                                  learningFactor,velocityWeight,
                                timesToAttemptPointGenerationWithinHyperSphere
            );

            return particleUpdater;
        }

        void printLoadedPatternsInfo(std::vector<Pattern *> *patterns,
                                     std::string headerInfo) {
            std::stringstream ss;
            ss << "[PATTERNS_" << headerInfo << "]\n";

            int sum = 0;
            for (int i = 0; i < patterns->size(); i++) {
                sum += (*patterns)[i]->size();
                ss << "Pattern["
                << i
                << "] ....................................... "
                << (*patterns)[i]->size() << std::endl;
            }
//            string temp = "\u222A";
            ss << "-------------------------------------------------+ " << sum;

            logger::log(ss.str());
        }
    }
}
