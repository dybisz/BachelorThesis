INSTALL_ROOT_PATH = \
$(addsuffix '/make/' , $(shell find . -mindepth 1 -maxdepth 1 -type d 2>/dev/null))

#--------------------------------------------
CLEAN=clean
ALL=all
INSTALL=install
#--------------------------------------------

RULE_NAME := all

ifeq ($(MAKECMDGOALS),${CLEAN})
	RULE_NAME := clean
endif

ifeq ($(MAKECMDGOALS),${INSTALL})
	RULE_NAME := install
endif

#--------------------------------------------

${ALL}:${INSTALL_ROOT_PATH}

${CLEAN}:${INSTALL_ROOT_PATH}

${INSTALL}:${INSTALL_ROOT_PATH}

#--------------------------------------------

$(INSTALL_ROOT_PATH):
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External: $@'
	@echo ${INFO_SEPARATOR}
	@$(MAKE) ${RULE_NAME} -C $@
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External $@ Finished'
	@echo