#!/bin/bash

######################################################################
#-------------------------- MAKE EXTERNALS --------------------------#
######################################################################

# Add paths to dir including makefile (not the makefile itself)
# Optionally Specify a rule
# E.g. MAKE_EXTERNAL = /path/to/make/ install

MAKE_EXTERNAL[0]='../../error/make/'
MAKE_EXTERNAL_RULE[0]='install'