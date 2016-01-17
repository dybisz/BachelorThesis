#!/usr/bin/env bash


MAIN_DIR_LOG="./logs/HILL_CLIMBER_STATES"
DIR_LOG="HILL_CLIMBER"

mkdir -p ${MAIN_DIR_LOG}

# :::::::::::::::::::::::::::
# ::::: S E T T I N G S :::::
# :::::::::::::::::::::::::::

#######################
##### ITERATIONS ######
#######################
MAX_ITER=10000

#################
##### WORDS #####
#################
WORDS=550

###################
##### CLASSES #####
###################
CLASSES=4

###################
##### STATES ######
###################
ENTRY_COUNT_STATES=9
STATES[0]=15
STATES[1]=35
STATES[2]=50
STATES[3]=65
STATES[4]=80
STATES[5]=105
STATES[6]=120
STATES[7]=135
STATES[8]=150

####################
##### ALPHABET #####
####################
ENTRY_COUNT_ALPHABET=1
ALPHABET[0]=6

###################
##### NATIVES #####
###################
NATIVE_XLS_PATH="./res/digits/Natives.xls"

#####################
##### FOREIGNS ######
#####################
ENTRY_COUNT_FOREIGN_XLS_PATH=1
FOREIGN_XLS_PATH[0]="./res/digits/Foreigns_02_005_XOR.xls"

# :::::::::::::::::
# ::::: R U N :::::
# :::::::::::::::::

#
# o  [Arguments]
# |- $1: States Number
# |- $2: Alphabet Size
# |- $3: Foreign Xls
# |- $4: Directory Name
#
run_optimizer(){
    echo "---------------------"
    echo "Starting Hill Climber"
    echo "States : " $1
    echo "Classes : " ${CLASSES}
    echo "Alphabet Size : " $2
    echo "Native Path : " ${NATIVE_XLS_PATH}
    echo "Foreign Path : " $3
    echo "DIR Path : " $4
    echo "---------------------"

    ./bin/pattern_recognizer -E 1 \
        --log-dir $4 \
        --log-main-dir ${MAIN_DIR_LOG} \
        -I ${MAX_ITER} \
        -N ${NATIVE_XLS_PATH} \
        -F $3 \
        -H $1 \
        -U ${CLASSES} \
        -u ${WORDS} \
        -A $2

}

for (( p=0; p<${ENTRY_COUNT_FOREIGN_XLS_PATH}; p++ )) do
    for (( states=0; states<${ENTRY_COUNT_STATES}; states++ )) do
            for ((a=0; a < ${ENTRY_COUNT_ALPHABET}; a++)) do
				for ((i=0;i<4;i++)) do
                run_optimizer ${STATES[$states]} ${ALPHABET[$a]} ${FOREIGN_XLS_PATH[$p]} "c${CLASSES}_s${STATES[$states]}"
				done
            done
    done
done
