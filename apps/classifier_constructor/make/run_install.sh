#!/bin/bash

###############################################


source ./struct_config.sh >/dev/null
source ./proj_config.sh >/dev/null

###############################################

for i in "$@"
do
case $i in
    -i=*|--install-root=*)
    INSTALL_ROOT_PATH="${i#*=}"
    ;;
    *)
            # unknown option
    ;;
esac
done

PROJECT_ROOT=..

###############################################
# INSTALLING
###############################################

mkdir -p ${INSTALL_ROOT_PATH}/${PROJ_CODE_NAME}
cp -rfu ${PROJECT_ROOT}/${STRUCT_BIN}/${PROJ_CODE_NAME} ${INSTALL_ROOT_PATH}/${PROJ_CODE_NAME}

cp -rfu ${PROJECT_ROOT}/README.txt ${INSTALL_ROOT_PATH}/${PROJ_CODE_NAME}
cp -rfu ${PROJECT_ROOT}/scripts/run_example.sh ${INSTALL_ROOT_PATH}/${PROJ_CODE_NAME}
