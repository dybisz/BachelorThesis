#!/bin/bash

#############################################################
# GLOBAL CONFIG
#############################################################

# Assume we start from root of app
CONFIG_ROOT_PATH=./scripts

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

source ${CONFIG_ROOT_PATH}/config.cfg
source ${CONFIG_ROOT_PATH}/pso/common.cfg


#############################################################
# Settings
#############################################################

MAIN_DIR_LOG=${APP_ROOT_PATH}/"logs/PSO/F_CROSSEDOUT/ALPHABET_4"
DIR_LOG="PSO"
mkdir -p ${MAIN_DIR_LOG}

MAX_ITER=${PSO_MAX_ITER}
SWARM_SIZE=${PSO_SWARM_SIZE}
MAX_VEL=${PSO_MAX_VEL}

ALPHABET_SIZE_START=4
ALPHABET_SIZE_END=4

STATES_PER_NATIVE_START=1
STATES_PER_NATIVE_END=5

STATES_PER_FOREIGN_MULTIPLIER_COUNT=3
STATES_PER_FOREIGN_MULTIPLIERS[0]=1
STATES_PER_FOREIGN_MULTIPLIERS[1]=2
STATES_PER_FOREIGN_MULTIPLIERS[2]=4

NATIVE_CLASS_COUNT=10
NATIVE_XLS_PATH=${APP_ROOT_PATH}/"res/digits/Natives.xls"

FOREIGN_XLS_PATH_COUNT=1
FOREIGN_XLS_PATH[0]=${APP_ROOT_PATH}/"res/digits/Foreigns_CrossedOut.xls"

DIR_SUB_NAME[0]='F_CROSSEDOUT'


#############################################################
# Run
#############################################################

#
# $1: States Per Native
# $2: States Per Foreign
# $3: Alphabet size
# $4: Foreign path
# $5: DIR path
#
run_optimizer(){
    echo "---------------------"
    echo "Starting Recognizer"
    echo "States per Native : " $1
    echo "States per Foreign : " $2
    echo "Alphabet size : " $3
    echo "Native Path : " ${NATIVE_XLS_PATH}
    echo "Foreign Path : " $4
    echo "DIR Path : " $5
    echo "---------------------"

    $APP_EXEC_PATH -E 0 \
        --log-dir $5 \
        --log-main-dir ${MAIN_DIR_LOG} \
        -I ${MAX_ITER} \
        -S ${SWARM_SIZE} \
        -N ${NATIVE_XLS_PATH} \
        -F $4 \
        --cl-states-native $1 \
        --cl-states-foreign $2 \
        --cl-alph-size $3 \
        --max-vel ${MAX_VEL}

}

for (( p=0; p<${FOREIGN_XLS_PATH_COUNT}; p++ )) do
    for (( n=${STATES_PER_NATIVE_START}; n<=${STATES_PER_NATIVE_END}; n++ )) do
        for (( f=0; f<${STATES_PER_FOREIGN_MULTIPLIER_COUNT}; f++ )) do
            for ((a=${ALPHABET_SIZE_START}; a <= ${ALPHABET_SIZE_END}; a++)) do

				NATIVE_STATES_TOTAL_COUNT=$(($n*${NATIVE_CLASS_COUNT}))
                STATES_PER_FOREIGN=$((${NATIVE_STATES_TOTAL_COUNT}*${STATES_PER_FOREIGN_MULTIPLIERS[$f]}))

                run_optimizer $n ${STATES_PER_FOREIGN} $a ${FOREIGN_XLS_PATH[$p]} \
					"${DIR_LOG}__${DIR_SUB_NAME[p]}__NSTATES_${NATIVE_STATES_TOTAL_COUNT}__FSTATES_${STATES_PER_FOREIGN}__ALPHABET_${a}"

            done
        done
    done
done