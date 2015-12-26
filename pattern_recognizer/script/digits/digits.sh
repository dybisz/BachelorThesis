#!/bin/bash

MAIN_DIR_LOG="./logs/DIGITS"
DIR_LOG="DIGITS"

#############################################################
# Settings
#############################################################

MAX_ITER=100
SWARM_SIZE=50

STATES_PER_NATIVE=2
STATES_PER_FOREIGN=2
ALPHABET_SIZE=4

NATIVE_XLS_PATH="./res/digits_short/short_Natives.xls"
FOREIGN_XLS_PATH="./res/digits_short/short_Foreign_90ccl.xls"


#############################################################
# Run
#############################################################


#
# $1: Tool Path
# $2: Start State
# $3: End States
# $4: Log dir
#
run_optimizer(){
    echo "---------------------"
    echo "Starting Recognizer"
    echo "Native Path: " ${NATIVE_XLS_PATH}
    echo "Foreign Path: " ${FOREIGN_XLS_PATH}
    echo "---------------------"

    ./bin/pattern_recognizer -E 0 \
        --log-dir ${DIR_LOG} \
        --log-main-dir ${MAIN_DIR_LOG} \
        -I ${MAX_ITER} \
        -S ${SWARM_SIZE} \
        -N ${NATIVE_XLS_PATH} \
        -F ${FOREIGN_XLS_PATH} \
        --cl-states-native ${STATES_PER_NATIVE} \
        --cl-states-foreign ${STATES_PER_FOREIGN} \
        --cl-alph-size ${ALPHABET_SIZE}
}

run_optimizer
