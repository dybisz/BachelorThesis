#!/usr/bin/env bash

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

################
##### LOGS #####
################

MAIN_DIR_LOG=${APP_ROOT_PATH}/"logs/HILL_CLIMBER"
DIR_LOG="HILL_CLIMBER"

mkdir -p ${MAIN_DIR_LOG}

####################
##### SETTINGS #####
####################

MAX_ITER=1000
STATES=150
ALPHABET=12
CLASSES=3
PATTERNS_PER_CLASS=350
NATIVE_XLS_PATH=${APP_ROOT_PATH}/"res/digits/Natives.xls"
FOREIGN_XLS_PATH=${APP_ROOT_PATH}/"res/digits/Foreign_90ccl.xls"

################
##### RUN ######
################

run_optimizer(){
    echo "---------------------"
    echo "Starting Recognizer"
    echo "Native Path: " ${NATIVE_XLS_PATH}
    echo "Foreign Path: " ${FOREIGN_XLS_PATH}
    echo "---------------------"

    $APP_EXEC_PATH -E 1 \
        --log-dir ${DIR_LOG} \
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