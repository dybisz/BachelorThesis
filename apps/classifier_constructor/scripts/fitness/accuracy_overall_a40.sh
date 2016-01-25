#!/usr/bin/env bash

#############################################################
# GLOBAL CONFIG
#############################################################

# Assume we start from root of app
CONFIG_ROOT_PATH=../scripts

for i in "$@"
do
case $i in
    -c=*|--config-root=*)
    CONFIG_ROOT_PATH="${i#*=}"
    ;;
    *)
            # unknown option
    ;;
esac
done

source ${CONFIG_ROOT_PATH}/fitness/config.cfg
source ${CONFIG_ROOT_PATH}/fitness/common.cfg


#############################################################
# Settings
#############################################################

MAIN_DIR_LOG="logs/FITNESS/ACCURACY_OVERALL"
DIR_LOG="ALPHABET_40"
FITNESS_TYPE=1

mkdir -p ${MAIN_DIR_LOG}

ALPHABET_SIZE=40

STATES_PER_NATIVE=2
STATES_PER_FOREIGN_MULTIPLIER=1

CLASSES_COUNT_START=10
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
    --log-main-dir ${MAIN_DIR_LOG} \
    --fit ${FITNESS_TYPE}


}

for ((i=1; i <= ${REPEAT_TIMES}; i++)) do
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
	done;
done
