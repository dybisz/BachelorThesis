#!/usr/bin/env bash


MAIN_DIR_LOG="./logs/KUBA_3_ALT"
DIR_LOG="KUBA_3_ALT"

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
ENTRY_WORDS_COUNT=3
WORDS[0]=250
WORDS[1]=500
WORDS[2]=750

###################
##### CLASSES #####
###################
CLASSES=10

###################
##### STATES ######
###################
ENTRY_COUNT_STATES=1
STATES[0]=40

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
# |- $5: Words
# |- $6: Classes
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
    echo "WORDS : " $5
    echo "CLASSES : " $6
    echo "---------------------"

    ../../bin/hcc -E 1 \
        --log-dir $4 \
        --log-main-dir ${MAIN_DIR_LOG} \
        -I ${MAX_ITER} \
        -N ${NATIVE_XLS_PATH} \
        -F $3 \
        -H $1 \
        -U $6 \
        -u $5 \
        -A $2

}

for (( p=0; p<${ENTRY_COUNT_FOREIGN_XLS_PATH}; p++ )) do
    for (( states=0; states<${ENTRY_COUNT_STATES}; states++ )) do
            for ((a=0; a < ${ENTRY_COUNT_ALPHABET}; a++)) do
                for ((w=0; w < ${ENTRY_WORDS_COUNT}; w++)) do
                    for ((c=1; c <= ${CLASSES}; c++)) do
                        run_optimizer ${STATES[$states]} ${ALPHABET[$a]} ${FOREIGN_XLS_PATH[$p]} "${DIR_LOG}_${DIR_SUB_NAME[fpath]}_w${WORDS[$w]}_a${ALPHABET[$a]}_s${STATES[$s]}" $WORDS[$w] $c
                    done
                done
            done
    done
done