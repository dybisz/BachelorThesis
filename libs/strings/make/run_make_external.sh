#!/bin/bash

source ./make_external_config.sh >/dev/null

for (( p=0; p<${#MAKE_EXTERNAL[@]}; p++ )) do
    make ${MAKE_EXTERNAL_RULE[$p]} -C ${MAKE_EXTERNAL[$p]} >/dev/null
    ERROR_CODE=$?

    if [ $ERROR_CODE -ne 0 ]; then
        break;
    fi
done

exit ${ERROR_CODE}