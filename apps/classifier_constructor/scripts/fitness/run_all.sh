#!/usr/bin/env bash

#############################################################
# GLOBAL CONFIG
#############################################################

CONFIG_ROOT_PATH=../scripts

source ${CONFIG_ROOT_PATH}/fitness/config.cfg
source ${CONFIG_ROOT_PATH}/fitness/common.cfg

SCRIPTS_PATH=${CONFIG_ROOT_PATH}/fitness

${SCRIPTS_PATH}/accuracy_overall_a30_fm05.sh
${SCRIPTS_PATH}/accuracy_overall_a30_fm1.sh
${SCRIPTS_PATH}/accuracy_overall_a30_fm2.sh
${SCRIPTS_PATH}/accuracy_overall_a30_fm4.sh

#${SCRIPTS_PATH}/accuracy_overall_a10.sh
#${SCRIPTS_PATH}/accuracy_overall_a30.sh
#${SCRIPTS_PATH}/accuracy_overall_a40.sh

#${SCRIPTS_PATH}/sensitivity_overall_a10.sh
#${SCRIPTS_PATH}/sensitivity_overall_a30.sh
#${SCRIPTS_PATH}/sensitivity_overall_a40.sh

#${SCRIPTS_PATH}/precision_overall_a10.sh
#${SCRIPTS_PATH}/precision_overall_a30.sh
#${SCRIPTS_PATH}/precision_overall_a40.sh

#${SCRIPTS_PATH}/fmeasure_overall_a10.sh
#${SCRIPTS_PATH}/fmeasure_overall_a30.sh
#${SCRIPTS_PATH}/fmeasure_overall_a40.sh