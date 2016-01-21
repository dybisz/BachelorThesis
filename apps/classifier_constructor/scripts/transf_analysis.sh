#!/usr/bin/env bash

#############################################################
# GLOBAL CONFIG
#############################################################

APP_EXEC_PATH="../bin/cc"

NATIVE_XLS_PATH="../../../resources/digits/Natives.xls"
FOREIGN_XLS_PATH="../../../resources/digits/Foreign_90ccl.xls"

MIN_ALPHABET_SIZE=3
MAX_ALPHABET_SIZE=3

LOG_DIR="TRANSFORMATION"

################
##### RUN ######
################

run_optimizer(){
    echo "---------------------"
    echo "Starting Recognizer"
    echo "Native Path: " ${NATIVE_XLS_PATH}
    echo "Foreign Path: " ${FOREIGN_XLS_PATH}
    echo "---------------------"

    ../bin/cc -E 1 \
    -N ${NATIVE_XLS_PATH} \
    -F ${FOREIGN_XLS_PATH} \
    -r ${MIN_ALPHABET_SIZE} \
    -R ${MAX_ALPHABET_SIZE} \
    --log-dir ${LOG_DIR}

}

run_optimizer
