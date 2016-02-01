#!/usr/bin/env bash


MAIN_DIR_LOG="./logs/ALPHABET_TEST"
DIR_LOG="ALPHABET_TEST"

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
WORDS=250

###################
##### CLASSES #####
###################
CLASSES=4

###################
##### STATES ######
###################
ENTRY_COUNT_STATES=1
STATES[0]=30

####################
##### ALPHABET #####
####################
ENTRY_COUNT_ALPHABET=10
ALPHABET[0]=2
ALPHABET[1]=3
ALPHABET[2]=4
ALPHABET[3]=8
ALPHABET[4]=12
ALPHABET[5]=16
ALPHABET[6]=20
ALPHABET[7]=24
ALPHABET[8]=30
ALPHABET[9]=40

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
# |- $5: Number of classes
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

    ../../bin/hcc -E 1 \
        --log-dir $4 \
        --log-main-dir ${MAIN_DIR_LOG} \
        -I ${MAX_ITER} \
        -N ${NATIVE_XLS_PATH} \
        -F $3 \
        -H $1 \
        -U $5 \
        -u ${WORDS} \
        -A $2

}

for (( p=0; p<${ENTRY_COUNT_FOREIGN_XLS_PATH}; p++ )) do
    for (( states=0; states<${ENTRY_COUNT_STATES}; states++ )) do
            for ((a=0; a < ${ENTRY_COUNT_ALPHABET}; a++)) do
                for((c=1; c <= ${CLASSES}; c++)) do
                    run_optimizer ${STATES[$states]} ${ALPHABET[$a]} ${FOREIGN_XLS_PATH[$p]} "${DIR_LOG}_${DIR_SUB_NAME[fpath]}_w${WORDS}_a${ALPHATBET[$a]}_c${c}" ${c}
                done
            done
    done
done