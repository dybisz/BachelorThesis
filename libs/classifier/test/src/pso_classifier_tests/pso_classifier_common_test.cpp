//
// Created by jakub on 1/16/16.
//

#include "pso_classifier_tests/pso_classifier_common_test.h"

using namespace pso;

Particle createParticle_s4_r2(){
    unsigned int stateCount = 4;
    unsigned int symbolCount = 2;

    double posMin = 0.0f;
    double posMax = 5.0f;

    double velMin = 0.0f;
    double velMax = 5.0f;

    double maxVel = 1.0f;

    Point<double> pos(8);
    pos[0] = 2.0f;
    pos[1] = 3.0f;
    pos[2] = 3.0f;
    pos[3] = 4.0f;

    pos[4] = 4.0f;
    pos[5] = 3.0f;
    pos[6] = 3.0f;
    pos[7] = 4.0f;

    Point<double> vel(8);

    Particle p(posMin, posMax,
               velMin, velMax,
               maxVel,
               pos, vel);
    return p;
}