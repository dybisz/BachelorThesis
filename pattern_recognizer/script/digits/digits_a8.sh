#!/bin/bash

MAIN_DIR_LOG="./logs/DIGITS"
DIR_LOG="DIGITS"

mkdir -p ${MAIN_DIR_LOG}

#############################################################
# Settings
#############################################################

MAX_ITER=1000
SWARM_SIZE=150
MAX_VEL=0.6

NATIVE_CLASS_COUNT=10

STATES_PER_NATIVE_START=1
STATES_PER_NATIVE_END=5

STATES_PER_FOREIGN_MULTIPLIER_LAST_INDEX=2
STATES_PER_FOREIGN_MULTIPLIERS[0]=1
STATES_PER_FOREIGN_MULTIPLIERS[1]=1,5
STATES_PER_FOREIGN_MULTIPLIERS[2]=2

ALPHABET_SIZE_START=8
ALPHABET_SIZE_END=8

NATIVE_XLS_PATH="./res/digits/Natives.xls"

FOREIGN_XLS_LAST_INDEX=1
FOREIGN_XLS_PATH[0]="./res/digits/Foreigns_90cl.xls"
FOREIGN_XLS_PATH[1]="./res/digits/Foreign_90ccl.xls"

DIR_SUB_NAME[0]='Foreigns_90cl'
DIR_SUB_NAME[1]='Foreign_90ccl'


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
    echo "States per Native : " $1
    echo "States per Foreign : " $2
    echo "Alphabet size : " $3
    echo "Native Path : " ${NATIVE_XLS_PATH}
    echo "Foreign Path : " $4
    echo "DIR Path : " $5
    echo "---------------------"


    ./bin/pattern_recognizer -E 0 \
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

for (( p=0; p<=${FOREIGN_XLS_LAST_INDEX}; p++ )) do
    for (( n=${STATES_PER_NATIVE_START}; n<=${STATES_PER_NATIVE_END}; n++ )) do
        for (( f=0; f<=${STATES_PER_FOREIGN_MULTIPLIER_LAST_INDEX}; f++ )) do
            for ((a=${ALPHABET_SIZE_START}; a <= ${ALPHABET_SIZE_END}; a++)) do
                STATES_PER_FOREIGN=$(($n*${STATES_PER_FOREIGN_MULTIPLIERS[$f]}*${NATIVE_CLASS_COUNT}))
                run_optimizer $n ${STATES_PER_FOREIGN} $a ${FOREIGN_XLS_PATH[$p]} "${DIR_LOG}_${DIR_SUB_NAME[fpath]}_n${n}_f${STATES_PER_FOREIGN}_a${a}"
            done
        done
    done
done
