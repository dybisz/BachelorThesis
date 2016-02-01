#!/usr/bin/env bash


MAIN_DIR_LOG="./logs/WORDS_DECREASING"
DIR_LOG="WORDS_DECREASING"

mkdir -p ${MAIN_DIR_LOG}

# :::::::::::::::::::::::::::
# ::::: S E T T I N G S :::::
# :::::::::::::::::::::::::::

#######################
##### ITERATIONS ######
#######################
MAX_ITER=5000

#################
##### WORDS #####
#################
WORDS_COUNT=10
WORDS[0]=50
WORDS[1]=100
WORDS[2]=150
WORDS[3]=250
WORDS[4]=300
WORDS[5]=350
WORDS[6]=400
WORDS[7]=450
WORDS[8]=500
WORDS[9]=550


###################
##### CLASSES #####
###################
CLASSES=3

###################
##### STATES ######
###################
ENTRY_COUNT_STATES=1
STATES[0]=30

####################
##### ALPHABET #####
####################
ENTRY_COUNT_ALPHABET=1
ALPHABET[0]=30

###################
##### NATIVES #####
###################
NATIVE_XLS_PATH="../../../../resources/digits/Natives.xls"

#####################
##### FOREIGNS ######
#####################
ENTRY_COUNT_FOREIGN_XLS_PATH=1
FOREIGN_XLS_PATH[0]="../../../../resources/digits/Foreigns_CrossedOut.xls"


# :::::::::::::::::
# ::::: R U N :::::
# :::::::::::::::::

#
# o  [Arguments]
# |- $1: States Number
# |- $2: Alphabet Size
# |- $3: Foreign Xls
# |- $4: Directory Name
# |- $5: Number of words
#
run_optimizer(){
    echo "---------------------"
    echo "Starting Hill Climber"
    echo "States : " $1
    echo "Classes : " ${CLASSES}
    echo "Alphabet Size : " $2
    echo "Native Path : " ${NATIVE_XLS_PATH}
    echo "Foreign Path : " $3
    echo "WORDS : " $4
    echo "---------------------"

    ../../bin/hcc -E 1 \
        --log-dir $4 \
        --log-main-dir ${MAIN_DIR_LOG} \
        -I ${MAX_ITER} \
        -N ${NATIVE_XLS_PATH} \
        -F $3 \
        -H $1 \
        -U ${CLASSES} \
        -u $5 \
        -A $2

}

for (( p=0; p<${ENTRY_COUNT_FOREIGN_XLS_PATH}; p++ )) do
    for (( states=0; states<${ENTRY_COUNT_STATES}; states++ )) do
            for ((a=0; a < ${ENTRY_COUNT_ALPHABET}; a++)) do
                for((w=0; w<${WORDS_COUNT}; w++)) do
                    run_optimizer ${STATES[$states]} ${ALPHABET[$a]} ${FOREIGN_XLS_PATH[$p]} "${DIR_LOG}_${DIR_SUB_NAME[fpath]}_w${WORDS[$w]}_a${ALPHATBET[$a]}_c${c}" ${WORDS[$w]}
                done
            done
    done
done