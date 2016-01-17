#!/bin/bash

######################################################################
#-------------------------- MAKE EXTERNALS --------------------------#
######################################################################

# Add paths to dir including makefile (not the makefile itself)
# Optionally Specify a rule
# E.g. MAKE_EXTERNAL = /path/to/make/ install

MAKE_EXTERNAL[0]='../../patterns/make/'
MAKE_EXTERNAL_RULE[0]='install'

MAKE_EXTERNAL[1]='../../pso/make/'
MAKE_EXTERNAL_RULE[1]='install'

MAKE_EXTERNAL[2]='../../math/make/'
MAKE_EXTERNAL_RULE[2]='install'

MAKE_EXTERNAL[3]='../../strings/make/'
MAKE_EXTERNAL_RULE[3]='install'