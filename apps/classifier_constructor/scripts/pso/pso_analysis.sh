#!/usr/bin/env bash

#############################################################
# GLOBAL CONFIG
#############################################################

APP_EXEC_PATH="../bin/cc"

NATIVE_XLS_PATH="../../../resources/digits/Natives.xls"
FOREIGN_XLS_PATH="../../../resources/digits/Foreign_90ccl.xls"

#############################################################
# Settings
#############################################################

MAIN_DIR_LOG="logs/PSO__A30__STATES_PER-NATIVE_2__STATES_MULTIP_FOREIGN_2"
DIR_LOG="PSO"
mkdir -p ${MAIN_DIR_LOG}

MAX_ITER=1000
SWARM_SIZE=100
MAX_VEL=10

ALPHABET_SIZE=30

STATES_PER_NATIVE=2
STATES_PER_FOREIGN_MULTIPLIER=1

CLASSES_COUNT_START=1
CLASSES_COUNT_END=10

OBJECTS_PER_CLASS=900

#############################################################
# Run
#############################################################

#
# $1: States Per Native
# $2: States Per Foreign
# $3: Alphabet size
# $4: Native path
# $5: Foreign path
# $6: Number of Classes
# $7: Objects per Class
# $8: DIR path
#
run_optimizer(){
    echo "---------------------"
    echo "Starting Recognizer"
    echo "States per Native :       " $1
    echo "States per Foreign :      " $2
    echo "Alphabet size :           " $3
    echo "Native Path :             " $4
    echo "Foreign Path :            " $5
    echo "Number of Classes :       " $6
    echo "Object per Class :        " $7
    echo "DIR Path :                " $8
    echo "---------------------"

    $APP_EXEC_PATH -E 0 \
    -I ${MAX_ITER} \
    -S ${SWARM_SIZE} \
    --max-vel ${MAX_VEL} \
    --cl-states-native $1 \
    --cl-states-foreign $2 \
    --cl-alph-size $3 \
    -N $4 \
    -F $5 \
    -U $6 \
    -u $7 \
    --log-dir $8 \
    --log-main-dir ${MAIN_DIR_LOG}


}


for ((c=${CLASSES_COUNT_START}; c <= ${CLASSES_COUNT_END}; c++)) do
    NATIVE_STATES_TOTAL_COUNT=$((${STATES_PER_NATIVE}*${c}))
    STATES_PER_FOREIGN=$((${NATIVE_STATES_TOTAL_COUNT}*${STATES_PER_FOREIGN_MULTIPLIER}))

    run_optimizer   ${STATES_PER_NATIVE} \
                    ${STATES_PER_FOREIGN} \
                    ${ALPHABET_SIZE} \
                    ${NATIVE_XLS_PATH} \
                    ${FOREIGN_XLS_PATH} \
                    ${c} \
                    ${OBJECTS_PER_CLASS} \
                    "${DIR_LOG}__CLASSES_${c}"
done
