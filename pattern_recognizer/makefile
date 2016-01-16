######################################################################
#--------------------------------------------------------------------#
#---------------------------- COMMENTS ------------------------------#
#--------------------------------------------------------------------#
######################################################################
SHELL := /bin/bash
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

######################################################################
#--------------------------------0-----------------------------------#
#-------------------------- CONFIG SECTION --------------------------#
#--------------------------------------------------------------------#
######################################################################

PATH_TO_CONFIGS = .

include ${PATH_TO_CONFIGS}/app_config.sh

APP_NAME := $(CFG_APP_NAME)
APP_CODE_NAME := $(CFG_APP_CODE_NAME)

# MAKECMDGOALS is set to name of target rule
# Select INSTALL_ROOT_PATH
ifeq ($(MAKECMDGOALS),$(INSTALL_RULE_NAME))
	INSTALL_ROOT_PATH := $(CFG_INSTALL_PATH)
else
	INSTALL_ROOT_PATH := $(shell pwd)
endif

######################################################################
#--------------------------------1-----------------------------------#
#------------------------ VARIABLES SECTION -------------------------#
#--------------------------------------------------------------------#
######################################################################

######################################################################
#------------------ DYNAMIC SUBSECTION - CAN MODIFY -----------------#
######################################################################

#---------------- UNIT TESTS ------------------#

# Path to root of googletest project
GTEST_ROOT = '../googletest'

#--------------- FILE EXTENSIONS --------------#

# c++ extension
CPP_EXT = .cpp
# cuda extension
CUDA_EXT = .cu

#-------------- PROJECT STRUCTURE -------------#

# Your header files
INC = include
# Your local libraries to be linked with the application
LIB = lib
# Build dumper. All your object files (*.o) will be located here
OBJ = build
# Source files and only source files, subdirectories are supported.
SRC = src
# Executables of your Application
BIN = bin
# Unit tests
TST = test
# All scripts to run all
SCRIPT=scripts

#------------- EXTERNAL MAKEFILES -------------#

# Paths to the Makefiles to be ran before this Makefile.
# Default target will be executed.
# Can be used to compile your static libraries before linking.
# Surrounded the path with '...' and separate different paths
# with a space.
MAKE_EXTERNAL = './${LIB}/excel_format/'

#---------------- LIBRARIES -------------------#

# Paths and names of libraries to link with
LIBS += -lpthread -lexcel_format

#----------------- INCLUDES -------------------#

# Paths to all Includes
INCLUDES += -I $(GTEST_ROOT)/include

#------------------- FLAGS --------------------#

# Use '-static' for static libraries
# Use '-shared' for shared libraries
L_FLAGS +=
C_FLAGS += -g -Wall -std=c++11
NVCC_FLAGS += -arch=sm_20


#----------------- PRINT OUTS -----------------#

# The separator will be printed between compiling objects
INFO_SEPARATOR = "|-------------------------------------------------------------------|"
INFO_FILLER = "  <<  "


######################################################################
#------------------ STATIC SUBSECTION - DO NOT MODIFY ---------------#
######################################################################

#----------------- COMPILERS -----------------#

CC = g++
NVCC = nvcc

#----------------- PROJECT MODULES -----------------#

CURRENT_PATH = ${shell pwd}

# List of all subdirectories in source directory
SRC_MODULES = $(shell find ${SRC} -type d 2>/dev/null)
# Adds each modules in include separately.
INC_MODULES =  $(addprefix -I , $(shell find ${INC} -type d 2>/dev/null))

#----------------- LIBRARIES MODULES -----------------#

# Variable representing comma ','
COMMA = ,

# The flags needed for ld path
LD_SHARED_PATH_FLAG = -Wl$(COMMA)-rpath

# Adds each module in lib folder to search for libs
LIB_MODULES = $(shell find ${INSTALL_ROOT_PATH}/${LIB} -type d 2>/dev/null)

# Add link flag to all LIB_MODULES
LIB_LINK_MODULES = $(addprefix -L , $(LIB_MODULES))

# The paths to all shared libraries
LIB_LINK_RPATH = $(addprefix ${LD_SHARED_PATH_FLAG} , $(LIB_MODULES))

# All Lib modules to include
LIB_INC_MODULES = $(addprefix -I , $(shell find ${LIB} -type d 2>/dev/null))

${LIB_MODULES_FUN}

LIBS += ${LIB_LINK_MODULES}
INCLUDES += ${INC_MODULES} ${LIB_INC_MODULES}

L_FLAGS += ${LIBS} ${LIB_LINK_RPATH}
C_FLAGS += ${INCLUDES} -MMD
NVCC_FLAGS +=

#----------------- SOURCE/OBJECT FILES -----------------#

# All source files
# [2>/dev/null] is added to supresss the 'file not found'
# message when inititing project structure for the first time
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

# All
debug: init_scripts link utest

# Release rule
link: $(MAKE_EXTERNAL) info_prefix init_project ${APP_CODE_NAME} info_suffix

# Install rule
${INSTALL_RULE_NAME}: clean_bin install_init link install_post

# Unit Test rule, assumes that $(TST) has a makefile inside
utest:
	@$(MAKE) -C $(TST)

################################################
#--------------- LINKER / COMPILER ------------#
################################################

#------------------ LINKER --------------------#

# Used in debug
${APP_CODE_NAME}: ${OBJECTS}
	@$(CC) -o ${BIN}/${APP_CODE_NAME} $^ $(L_FLAGS)

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

# Make external makefiles
$(MAKE_EXTERNAL):
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External: $@'
	@echo ${INFO_SEPARATOR}
	@$(MAKE) -C $@
	@echo ${INFO_SEPARATOR}
	@echo 'Compiling External $@ Finished'
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
	@echo ${INFO_FILLER}"MAKING:" ${APP_NAME}
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
