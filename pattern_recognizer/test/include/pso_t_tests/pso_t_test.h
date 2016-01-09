//
// Created by jakub on 1/6/16.
//

#ifndef BACHELOR_THESIS_PSO_T_TEST_H
#define BACHELOR_THESIS_PSO_T_TEST_H

#include <pso/pso_t.h>
#include <pso/pso_common.h>
#include <pso/particle_decoder_t.h>
#include <pso/particle_factory_t.h>
#include <particle_decoder_test.h>
#include <fitness_updater_test.h>
#include <neighbourhood_updater_test.h>
#include <particle_updater_test.h>

/*
 * Creates a specific small particle
 * Word: 011 ends in state 2.
 * Word: 0 ends in state 1.
 */
pso::Particle_T createParticle_s4_r2();

PSO_T createPSOInstance();

#endif //BACHELOR_THESIS_PSO_T_TEST_H
