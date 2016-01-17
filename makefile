#--------------------------------------------
# RULE NAMES
#--------------------------------------------

# Cleans builds of apps and libs
CLEAN=clean
# Cleans builds of apps
CLEAN_APPS=clean_apps
# Cleans builds of libs
CLEAN_LIBS=clean_libs

# Builds apps and libs
MAKE_ALL=make_all
# Makes apps
MAKE_APPS=make_apps
# Makes libs
MAKE_LIBS=make_libs

# Install both libs and apps
INSTALL=install
# Installs apps
INSTALL_APPS=install_apps
# Installs libs
INSTALL_LIBS=install_libs

# Cleans dependencies
CLEAN_DEPENDENCIES=clean_deps

#--------------------------------------------
# FOLDERS
#--------------------------------------------

APPS=apps
LIBS=libs
DEPENDENCIES=dependencies

#--------------------------------------------
# APPS/LIBS
#--------------------------------------------

# Find all makefiles in apps
APPS_MODULES = \
$(addsuffix '/make' , $(shell find ${APPS} -mindepth 1 -maxdepth 1 -type d 2>/dev/null))

# Find all makefiles in libs
LIBS_MODULES = \
$(addsuffix '/make' , $(shell find ${LIBS} -mindepth 1 -maxdepth 1 -type d 2>/dev/null))

#--------------------------------------------
# EXTERNAL RULE
#--------------------------------------------

# Set the rule name to run for all makefiles

RULE_NAME := all

ifeq ($(MAKECMDGOALS),${CLEAN})
	RULE_NAME := clean
endif

ifeq ($(MAKECMDGOALS),${CLEAN_APPS})
	RULE_NAME := clean
endif

ifeq ($(MAKECMDGOALS),${CLEAN_LIBS})
	RULE_NAME := clean
endif

ifeq ($(MAKECMDGOALS),${INSTALL_APPS})
	RULE_NAME := install
endif

ifeq ($(MAKECMDGOALS),${INSTALL_APPS})
	RULE_NAME := install
endif

ifeq ($(MAKECMDGOALS),${INSTALL_LIBS})
	RULE_NAME := install
endif

#--------------------------------------------
# DEPENDENCIES
#--------------------------------------------

DEPENDENCIES_INCLUDES =\
$(shell find ${DEPENDENCIES}/include/  \
-mindepth 1 -maxdepth 1 ! -name 'excel_format')

DEPENDENCIES_LIBS =\
$(shell find ${DEPENDENCIES}/lib/ \
-mindepth 1 -maxdepth 1 ! -name 'excel_format')

#--------------------------------------------
# RULES
#--------------------------------------------

${MAKE_ALL}: ${MAKE_APPS} ${MAKE_LIBS}

${MAKE_APPS}: ${APPS_MODULES}

${MAKE_LIBS}: ${LIBS_MODULES}


${CLEAN}: ${CLEAN_APPS} ${CLEAN_LIBS}

${CLEAN_APPS}: ${APPS_MODULES}

${CLEAN_LIBS}: ${LIBS_MODULES}

${INSTALL}: ${INSTALL_APPS} ${INSTALL_LIBS}

${INSTALL_APPS}: ${APPS_MODULES}

${INSTALL_LIBS}: ${LIBS_MODULES}

${CLEAN_DEPENDENCIES}:
	@echo "Removing:"
	@$(foreach var, ${DEPENDENCIES_INCLUDES}, echo ${var};)
	@$(foreach var, ${DEPENDENCIES_LIBS}, echo ${var};)
	@$(foreach var, ${DEPENDENCIES_INCLUDES}, rm -rf ${var})
	@$(foreach var, ${DEPENDENCIES_LIBS}, rm -rf ${var})

#--------------------------------------------

$(APPS_MODULES):
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External: $@'
	@echo ${INFO_SEPARATOR}
	@$(MAKE) ${RULE_NAME} -C $@
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External $@ Finished'
	@echo

$(LIBS_MODULES):
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External: $@'
	@echo ${INFO_SEPARATOR}
	@$(MAKE) ${RULE_NAME} -C $@
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External $@ Finished'
	@echo

#--------------------------------------------

JAVA_JDK=/usr/lib/jvm/java-8-oracle

GUI:
	cd gui && ant -DJAVA_HOME="${JAVA_JDK}"
