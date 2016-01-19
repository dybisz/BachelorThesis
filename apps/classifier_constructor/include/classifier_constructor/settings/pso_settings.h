//
// Created by jakub on 1/19/16.
//

#ifndef BACHELOR_THESIS_PSO_SETTINGS_H
#define BACHELOR_THESIS_PSO_SETTINGS_H

#include <string>

namespace settings {
    // Maximum iterations of PSO algorithm
    extern int MAX_ITER;

    extern double LEARNING_FACTOR;

    extern double PARTICLE_VEL_WEIGHT;

    // When encoding particle back to automaton
    // each dimension must be casted down to integer value.
    // If p[i] > x.5 then take the ceiling.
    // otherwise take the floor.
    // Formally:
    //      encodedValue = (int)p[i]
    //      delta = p[i] - encodedValue
    //      if delta > ENCODING_DELTA
    //          encodedValue++
    //
    extern double ENCODING_DELTA;

    // Becouse of the nature of the encoding the
    // upper interval bound must a bit less than:
    // n + ENCODING_DELTA
    extern double UPPER_BOUND_ERR;

    // The maximum change that particle can make in single iteration
    extern double MAX_VELOCITY;

    extern int SWARM_SIZE;


//------------------------------------------------------------------------------

    void setPSOFlags();

    /*
     * Prints all the settings.
     * TODO Do it automatically.
     */
    void printPSOSettings();
}


#endif //BACHELOR_THESIS_PSO_SETTINGS_H
