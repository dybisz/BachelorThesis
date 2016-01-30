#!/usr/bin/env bash

#############################################################
# GLOBAL CONFIG
#############################################################

# Assume we start from root of app
CONFIG_ROOT_PATH=../scripts

SCRIPTS_PATH=${CONFIG_ROOT_PATH}/pso

${SCRIPTS_PATH}/pso_a10_fm05.sh
${SCRIPTS_PATH}/pso_a10_fm1.sh
${SCRIPTS_PATH}/pso_a10_fm2.sh

${SCRIPTS_PATH}/pso_a30_fm05.sh
${SCRIPTS_PATH}/pso_a30_fm1.sh
${SCRIPTS_PATH}/pso_a30_fm2.sh

${SCRIPTS_PATH}/pso_a40_fm05.sh
${SCRIPTS_PATH}/pso_a40_fm1.sh
${SCRIPTS_PATH}/pso_a40_fm2.sh
