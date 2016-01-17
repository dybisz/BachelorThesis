#!/usr/bin/env bash

################
##### LOGS #####
################

MAIN_DIR_LOG="./logs/HILL_CLIMBER"
DIR_LOG="HILL_CLIMBER"

mkdir -p ${MAIN_DIR_LOG}

####################
##### SETTINGS #####
####################

MAX_ITER=10000
STATES=35
ALPHABET=8
CLASSES=4
PATTERNS_PER_CLASS=550
NATIVE_XLS_PATH="./res/digits/Natives.xls"
FOREIGN_XLS_PATH="./res/digits/Foreigns_02_005_XOR.xls"

################
##### RUN ######
################

run_optimizer(){
    echo "---------------------"
    echo "Starting Recognizer"
    echo "Native Path: " ${NATIVE_XLS_PATH}
    echo "Foreign Path: " ${FOREIGN_XLS_PATH}
    echo "---------------------"

    ./bin/pattern_recognizer -E 1 \
        --log-dir "c${CLASSES}_a${ALPHABET}" \
        --log-main-dir ${MAIN_DIR_LOG} \
        -I ${MAX_ITER} \
        -N ${NATIVE_XLS_PATH} \
        -F ${FOREIGN_XLS_PATH} \
        -H ${STATES} \
        -U ${CLASSES} \
        -u ${PATTERNS_PER_CLASS} \
        -A ${ALPHABET}
}

run_optimizer
