######################################################################
#--------------------------------------------------------------------#
#---------------------------- COMMENTS ------------------------------#
#--------------------------------------------------------------------#
######################################################################

#---------------------------------------------------------------------
#
# Structure.
#
# This Makefile is split into:
# 1) Variables Section
# 	1.1) Dynamic subsection
# 	1.2) Static subsection - DO NOT MODIFY
# 2) Rules Section
# 	2.1) Static subsection - DO NOT MODIFY
# 	2.2) Dynamic subsection
# 3) Dependency Graph - DO NOT MODIFY
#
#
# As a user of this makefile You should not be modifing
# any of the static subsections.
#
#---------------------------------------------------------------------
#
# Compilers supported:
#
# 1) g++
# 2) nvcc
#
#---------------------------------------------------------------------
#
# Supports a particular project structure:
# Refer to Project Structure section to define the following folders:
#
# 1) INC: Header files of this application
# 2) LIB: Your, local Libraries to be linked with application
# 3) BLD: Build where your compiled object files are stored
# 4) SRC: Source files of this application
# 5) BIN: Binary files, executables of the application
#
#---------------------------------------------------------------------
#
# Tips:
#
# Use '\' to break new line
# Take special care of whitespaces, it might cause errors.
# $@ is the value of target
# $^ is the list of all prerequisites of the rule
# $< is just the first prerequisite
#
#---------------------------------------------------------------------
#
# TODO:
# (Lack of these features might cause bugs)
#
# Realese / Debug
# Support for gcc for .c files
# Currently only one extension per XX_EXT variable applies
# Support for unit tests
# Variable printouts
# Add usage
#
#---------------------------------------------------------------------
#
# Author:
#
# github.com/Jakub-Ciecierski
# jakub.ciecier@gmail.com
#
#---------------------------------------------------------------------
#
# For further information refer to:
# http://www.gnu.org/software/make/manual/make.html
#
#---------------------------------------------------------------------
#
# Changes log:
# 01.07.2015 - Created
# 26.10.2015 - Added Unit Test rule
# 08.11.2015 - OpenGL and CUDA libraries commented out
# 12.11.2015 - Added each module in include separately.
#	For example.
#	File:
#		./include/math/clustering/kmeans.h
#	can be included as:
#		#include "kmeans.h"
#	or:
#		#include "math/clustering/kmeans.h"
#
# 15.12.2015 - Added install rule
# 11.01.2016 - Made new clean functionality for libraries
# 11.01.2016 - Automatic header include and library
#				paths for all libraries in lib/
# 11.01.2016 - Added Config section.
#---------------------------------------------------------------------

######################################################################
#--------------------------------0-----------------------------------#
#--------------------------- RULE NAMES -----------------------------#
#--------------------------------------------------------------------#
######################################################################

INSTALL_RULE_NAME=install
RELEASE_RULE_NAME=release
EXTERNALS_RULE_NAME=externals

######################################################################
#--------------------------------0-----------------------------------#
#-------------------------- CONFIG SECTION --------------------------#
#--------------------------------------------------------------------#
######################################################################

PROJECT_ROOT = ..
PATH_TO_CONFIGS = ${PROJECT_ROOT}/make

INSTALL_ROOT_PATH := $(shell pwd)/${PROJECT_ROOT}/../..

# Path to directory containing
# common external libs in custom directory
EXTERNAL_LIBS_PATH=${INSTALL_ROOT_PATH}/dependencies
RELATIVE_EXTERNAL_LIBS_PATH=../dependencies

EXTERNAL_LIBS_INCLUDE_PATH=${EXTERNAL_LIBS_PATH}/include
EXTERNAL_LIBS_LIB_PATH=${EXTERNAL_LIBS_PATH}/lib

RELATIVE_EXTERNAL_LIBS_INCLUDE_PATH=${RELATIVE_EXTERNAL_LIBS_PATH}/include
RELATIVE_EXTERNAL_LIBS_LIB_PATH=${RELATIVE_EXTERNAL_LIBS_PATH}/lib

# Include make configurations
include ${PATH_TO_CONFIGS}/proj_config.sh
include ${PATH_TO_CONFIGS}/struct_config.sh
include ${PATH_TO_CONFIGS}/compiler_config.sh
include ${PATH_TO_CONFIGS}/make_external_config.sh

# Get runners scripts handles
RUN_INSTALL_SCRIPT:=${PATH_TO_CONFIGS}/run_install.sh -i=${INSTALL_ROOT_PATH}
RUN_RELEASE_SCRIPT:=${PATH_TO_CONFIGS}/run_release.sh
LIB_NAME_SCRIPT:=${PATH_TO_CONFIGS}/lib_name.sh

RUN_MAKE_EXTERNAL_SCRIPT:=${PATH_TO_CONFIGS}/run_make_external.sh -i=${EXTERNAL_LIBS_PATH}

######################################################################
#--------------------------------1-----------------------------------#
#------------------------ VARIABLES SECTION -------------------------#
#--------------------------------------------------------------------#
######################################################################

######################################################################
#------------------ DYNAMIC SUBSECTION - CAN MODIFY -----------------#
######################################################################


#--------------- FILE EXTENSIONS --------------#

# c++ extension
CPP_EXT = ${COMPILER_CC_EXT}
# cuda extension
CUDA_EXT = ${COMPILER_NVCC_EXT}

#-------------- PROJECT STRUCTURE -------------#

INC = ${PROJECT_ROOT}/${STRUCT_INC}
SRC = ${PROJECT_ROOT}/${STRUCT_SRC}
LIB = ${PROJECT_ROOT}/${STRUCT_LIB}
OBJ = ${PROJECT_ROOT}/${STRUCT_OBJ}
BIN = ${PROJECT_ROOT}/${STRUCT_BIN}
TST = ${PROJECT_ROOT}/${STRUCT_TST}
DOC = ${PROJECT_ROOT}/${STRUCT_DOC}
# All scripts to run all
SCRIPT=scripts

#---------------- LIBRARIES -------------------#

# Paths and names of libraries to link with
LIBS += -latl -lflagger -lptrec -llogger -lpso -ltransform -lstrings\
		-lmath -lparallel -ltime -lstrings -lcquality \
		-lclassifier \
		-lexcel_format

#----------------- INCLUDES -------------------#

# Paths to all Includes
INCLUDES +=

#------------------- FLAGS --------------------#

# Use '-static' for static libraries
# Use '-shared' for shared libraries
L_FLAGS +=
C_FLAGS += -g -std=c++11
NVCC_FLAGS += -arch=sm_20

#----------------- PRINT OUTS -----------------#

# The separator will be printed between compiling objects
INFO_SEPARATOR = "|-------------------------------------------------------------------|"
INFO_FILLER = "  <<  "


######################################################################
#------------------ STATIC SUBSECTION - DO NOT MODIFY ---------------#
######################################################################

#----------------- COMPILERS -----------------#

CC = ${COMPILER_CC}
NVCC = ${COMPILER_NVCC}

#----------------- PROJECT MODULES -----------------#

CURRENT_PATH = ${shell pwd}

# List of all subdirectories in source directory
SRC_MODULES = $(shell find ${SRC} -type d 2>/dev/null)

#----------------- INCLUDE MODULES -----------------#

# Finds all libraries in libs/include path
EXTERNAL_LIBS_INCLUDE_MODULES=$(addprefix -I ,\
$(shell find ${EXTERNAL_LIBS_INCLUDE_PATH} -maxdepth 1 -type d 2>/dev/null))

RELATVE_EXTERNAL_LIBS_INCLUDE_MODULES=$(addprefix -I ,\
$(shell find ${RELATIVE_EXTERNAL_LIBS_INCLUDE_PATH} -maxdepth 1 -type d 2>/dev/null))

# All Lib modules to include
LIB_INC_MODULES = $(addprefix -I , $(shell find ${LIB} -type d 2>/dev/null))

#----------------- LIBRARIES MODULES -----------------#

# Variable representing comma ','
COMMA = ,

# The flags needed for ld path
LD_SHARED_PATH_FLAG = -Wl$(COMMA)-rpath

#----------------- IN HOUSE LIBRARIES MODULES -----------------#

# Adds each module in lib folder to search for libs
LIB_MODULES = \
$(shell find ${INSTALL_ROOT_PATH}/${LIB} -type d 2>/dev/null)

# Add link flag to all LIB_MODULES
LIB_LINK_MODULES = $(addprefix -L , $(LIB_MODULES))

# The paths to all shared libraries
LIB_LINK_RPATH = $(addprefix ${LD_SHARED_PATH_FLAG} , $(LIB_MODULES))

#----------------- EXTERNAL LIBRARIES MODULES -----------------#

# Adds each module in lib folder to search for libs
EXTERNAL_LIB_MODULES = \
$(shell find ${EXTERNAL_LIBS_LIB_PATH} -type d 2>/dev/null)

RELATIVE_EXTERNAL_LIB_MODULES = \
$(shell find ${RELATIVE_EXTERNAL_LIBS_LIB_PATH} -type d 2>/dev/null)

# Add link flag to all LIB_MODULES
EXTERNAL_LIB_LINK_MODULES = \
$(addprefix -L , $(EXTERNAL_LIB_MODULES))

# Add link flag to all LIB_MODULES
RELATIVE_EXTERNAL_LIB_LINK_MODULES = \
$(addprefix -L , $(RELATIVE_EXTERNAL_LIB_MODULES))

# The paths to all shared libraries
EXTERNAL_LIB_LINK_RPATH = \
$(addprefix ${LD_SHARED_PATH_FLAG} , $(EXTERNAL_LIB_MODULES))

# The paths to all shared libraries
RELATIVE_EXTERNAL_LIB_LINK_RPATH = \
$(addprefix ${LD_SHARED_PATH_FLAG} , $(RELATIVE_EXTERNAL_LIB_MODULES))


#----------------- LIBS / INCLUDES -----------------#

LIBS += ${LIB_LINK_MODULES} ${LIB_LINK_RPATH} \
		${EXTERNAL_LIB_LINK_MODULES} ${EXTERNAL_LIB_LINK_RPATH} \
		${RELATIVE_EXTERNAL_LIB_LINK_MODULES} \
		${RELATIVE_EXTERNAL_LIB_LINK_RPATH}

INCLUDES += -I ${INC} ${LIB_INC_MODULES} \
		${EXTERNAL_LIBS_INCLUDE_MODULES} \
		${RELATIVE_EXTERNAL_LIBS_INCLUDE_MODULES}

#----------------- COMPILER FLAGS -----------------#

L_FLAGS += ${LIBS}
C_FLAGS += ${INCLUDES} -MMD
NVCC_FLAGS +=

#----------------- SOURCE/OBJECT FILES -----------------#

# All source files
# [2>/dev/null] is added to supresss the 'file not found'
# message when initiating project structure for the first time
# (src file does not exist at the beginning)
CPP_SOURCES = $(shell find ${SRC} -name *${CPP_EXT} 2>/dev/null)
CUDA_SOURCES = $(shell find ${SRC} -name *${CUDA_EXT} 2>/dev/null)

# All objects to be compiled
OBJECTS += $(addprefix ${OBJ}/,$(notdir $(CPP_SOURCES:${CPP_EXT}=.o)))
OBJECTS += $(addprefix ${OBJ}/,$(notdir $(CUDA_SOURCES:${CUDA_EXT}=.o)))

# Add modules to vpath
VPATH = ${SRC_MODULES}

######################################################################
#---------------------------------2----------------------------------#
#------------------------------ RULES -------------------------------#
#--------------------------------------------------------------------#
######################################################################

######################################################################
#------------------ STATIC SUBSECTION - DO NOT MODIFY ---------------#
######################################################################

################################################
#----------------- MAIN RULES -----------------#
################################################

all: compile_objects link run_test

compile_objects: init_project $(EXTERNALS_RULE_NAME) ${OBJECTS}

link: info_prefix init_project ${PROJ_CODE_NAME} info_suffix

link_without_test: compile_objects link compile_test

${INSTALL_RULE_NAME}: all
	@$(RUN_INSTALL_SCRIPT)

compile_test:
	@$(MAKE) link -C $(TST)

# Unit Test rule, assumes that $(TST) has a makefile inside
run_test:
	@$(MAKE) INSTALL_ROOT_PATH=${EXTERNAL_LIBS_PATH} -C $(TST)

################################################
#--------------- LINKER / COMPILER ------------#
################################################

#------------------ LINKER --------------------#

# Used in debug
${PROJ_CODE_NAME}: ${OBJECTS}
	@$(CC) -o ${BIN}/${PROJ_CODE_NAME} $^ $(L_FLAGS)

#----------------- COMPILERS ------------------#

# cpp compiler
$(OBJ)/%.o: %${CPP_EXT}
	@echo ${INFO_SEPARATOR}
	@echo 'COMPILING: ' $<
	@echo
	@$(CC) $(C_FLAGS) -c -o $@ $<

# cuda compiler
${OBJ}/%.o: %${CUDA_EXT}
	@echo ${INFO_SEPARATOR}
	@echo 'COMPILING: ' $<
	@echo
	@$(NVCC) $(NVCC_FLAGS) -c -o $@ $<

################################################
#----------------- EXTERNALS ------------------#
################################################

${EXTERNALS_RULE_NAME}:
	@echo
	@echo "Starting Externals"
	@echo
	@$(RUN_MAKE_EXTERNAL_SCRIPT)
	@echo
	@echo "Finishing Externals"
	@echo

######################################################################
#------------------ DYNAMIC SUBSECTION - CAN MODIFY -----------------#
######################################################################

################################################
#-------------- INITIALIZATION ----------------#
################################################

init_all: init_project init_scripts

# Creates all the directories of the project
init_project:
	@mkdir -p ${OBJ} ${BIN} ${SRC} ${LIB} ${INC} ${TST}

# Initializes scripts folder and a config script for exec path
init_scripts:
	@mkdir -p ${SCRIPT}
	@touch ./${SCRIPT}/config.cfg
	@chmod 755 ./${SCRIPT}/config.cfg
	$(shell > ./${SCRIPT}/config.cfg)
	$(shell echo "APP_ROOT_PATH="${INSTALL_ROOT_PATH} >> ./${SCRIPT}/config.cfg)
	$(shell echo "APP_EXEC_PATH="${INSTALL_ROOT_PATH}/${BIN}/${APP_CODE_NAME} \
	>> ./${SCRIPT}/config.cfg)

################################################
#---------------- INSTALLATION ----------------#
################################################

# TODO Seperate installation function
install_init:
	@echo "Install to directory: " ${INSTALL_ROOT_PATH}
	@mkdir -p ${INSTALL_ROOT_PATH}
	@echo "Installing resources"
	@cp -r ./res ${INSTALL_ROOT_PATH}
	@echo "Installing scripts"
	@cp -r ./${SCRIPT} ${INSTALL_ROOT_PATH}
	$(shell > ${INSTALL_ROOT_PATH}/${SCRIPT}/config.cfg)
	$(shell echo "APP_ROOT_PATH="${INSTALL_ROOT_PATH} \
	>> ${INSTALL_ROOT_PATH}/${SCRIPT}/config.cfg)
	$(shell echo "APP_EXEC_PATH="${INSTALL_ROOT_PATH}/${APP_CODE_NAME} \
	>> ${INSTALL_ROOT_PATH}/${SCRIPT}/config.cfg)
	@echo "Installing Libraries"
	@cp -r ${LIB} ${INSTALL_ROOT_PATH}

# This rule should be used to define the installation process.
# Add all requirement for your installation here.
# This will be ran after compilation.
install_post:
	@cp ${BIN}/${APP_CODE_NAME} ${INSTALL_ROOT_PATH}

################################################
#------------------- CLEAN --------------------#
################################################

clean: clean_obj clean_bin
	@$(MAKE) -C $(TST) clean

clean_obj:
	$(eval OBJECTS=$(shell find ${OBJ} -name *.o))
	$(eval DEPS=$(shell find ${OBJ} -name *.d))
	$(eval TMPS=$(shell find ${OBJ} -name *.~))
	@echo ${INFO_SEPARATOR}
	@echo
	@echo ${INFO_FILLER} "Cleaning: ${OBJ}/"
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo
	@echo "Object files:"
	@echo
	@$(foreach var, ${OBJECTS}, echo ${var};)
	@echo
	@echo ${INFO_SEPARATOR}
	@echo
	@echo "Dependency files:"
	@echo
	@$(foreach var, ${DEPS}, echo ${var};)
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@$(foreach var, ${OBJECTS}, rm -f ${var})
	@$(foreach var, ${DEPS}, rm -f ${var})
	@$(foreach var, ${TMPS}, rm -f ${var})
	@rm -rf ${OBJ}

clean_bin:
	$(eval BINS=$(shell find ${BIN} -type f))
	@echo ${INFO_SEPARATOR}
	@echo
	@echo ${INFO_FILLER} "Cleaning: ${BIN}/"
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo
	@echo "Binary Files:"
	@echo
	@$(foreach var, ${BINS}, echo ${var};)
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@$(foreach var, ${BINS}, rm -f ${var})
	@rm -rf ${BIN}

# Cleans all compiled objects within the lib directory
clean_lib:
	$(eval OBJS=$(shell find ${LIB} -name *.o))
	$(eval DEPS=$(shell find ${LIB} -name *.d))
	$(eval ST_LIBS=$(shell find ${LIB} -name *.a))
	$(eval SH_LIBS=$(shell find ${LIB} -name *.so))
	@echo ${INFO_SEPARATOR}
	@echo
	@echo ${INFO_FILLER} "Cleaning: ${LIB}/"
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo
	@echo "Object files:"
	@echo
	@$(foreach var, ${OBJS}, echo ${var};)
	@echo
	@echo ${INFO_SEPARATOR}
	@echo
	@echo "Dependency files:"
	@echo
	@$(foreach var, ${DEPS}, echo ${var};)
	@echo
	@echo ${INFO_SEPARATOR}
	@echo
	@echo "Static Libraries:"
	@echo
	@$(foreach var, ${ST_LIBS}, echo ${var};)
	@echo
	@echo ${INFO_SEPARATOR}
	@echo
	@echo "Shared Libraries:"
	@echo
	@$(foreach var, ${SH_LIBS}, echo ${var};)
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@$(foreach var, ${OBJS}, rm -f ${var})
	@$(foreach var, ${DEPS}, rm -f ${var})
	@$(foreach var, ${ST_LIBS}, rm -f ${var})
	@$(foreach var, ${SH_LIBS}, rm -f ${var})

clean_all: clean clean_lib

.PHONY: $(SUBDIRS) clean

################################################
#----------------- PRINT RULES-----------------#
################################################

info_prefix:
	@echo
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo
	@echo ${INFO_FILLER}"MAKING:" ${PROJ_NAME}
	@echo
	@echo

info_suffix:
	@echo
	@echo ${INFO_SEPARATOR}
	@echo
	@echo ${INFO_FILLER}"LINKING SUCCESSFULL"
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo

######################################################################
#---------------------------------3----------------------------------#
#---------------- DEPENDENCY GRAPH - DO NOT MODIFY ------------------#
#--------------------------------------------------------------------#
######################################################################

#--------------- DEPENDENCY GRAPH -------------#

# Automatic dependency graph generation
# Must be inserted at the end of the makefile
-include $(OBJECTS:.o=.d)
