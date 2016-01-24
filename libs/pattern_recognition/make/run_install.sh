#!/bin/bash

###############################################

source ./install_config.sh >/dev/null

###############################################

PROJECT_ROOT=..

###############################################
# INSTALLING
###############################################

mkdir -p ${INSTALL_ROOT_PATH}

mkdir -p ${INSTALL_LIB_ROOT_PATH}
mkdir -p ${INSTALL_INC_ROOT_PATH}

mkdir -p ${INSTALL_LIB_PATH}
mkdir -p ${INSTALL_INC_PATH}

echo Installing lib to directory ${INSTALL_LIB_PATH}
echo Installing includes to directory ${INSTALL_INC_PATH}

cp -rfu ${PROJECT_ROOT}/${STRUCT_INC}/* ${INSTALL_INC_PATH}
cp ${PROJECT_ROOT}/${STRUCT_OBJ}/${LIB_FULL_NAME} ${INSTALL_LIB_PATH}