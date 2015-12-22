#!/bin/bash

MAIN_DIR_LOG="./logs/DIGITS"
DIR_LOG="DIGITS"

#############################################################
# Settings
#############################################################

MAX_ITER=100
SWARM_SIZE=50

NATIVE_XLS_PATH="./res/digits/Natives.xls"
FOREIGN_XLS_PATH="./res/digits/Foreigns_90cl.xls"


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
        -F ${FOREIGN_XLS_PATH}
}

run_optimizer
