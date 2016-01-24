#!/bin/bash

######################################################################
#-------------------------- MAKE EXTERNALS --------------------------#
######################################################################

# Add paths to dir including makefile (not the makefile itself)
# Optionally Specify a rule
MAKE_EXTERNAL[0]='../../../libs/atl/make/'
MAKE_EXTERNAL_RULE[0]='install'

MAKE_EXTERNAL[1]='../../../libs/flagger/make/'
MAKE_EXTERNAL_RULE[1]='install'

MAKE_EXTERNAL[2]='../../../libs/pattern_recognition/make/'
MAKE_EXTERNAL_RULE[2]='install'

MAKE_EXTERNAL[3]='../../../libs/logger/make/'
MAKE_EXTERNAL_RULE[3]='install'

MAKE_EXTERNAL[4]='../../../libs/pso/make/'
MAKE_EXTERNAL_RULE[4]='install'

MAKE_EXTERNAL[5]='../../../libs/classifier_quality/make/'
MAKE_EXTERNAL_RULE[5]='install'

MAKE_EXTERNAL[6]='../../../libs/transformation/make/'
MAKE_EXTERNAL_RULE[6]='install'