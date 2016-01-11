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
#
#---------------------------------------------------------------------


######################################################################
#--------------------------------1-----------------------------------#
#------------------------ VARIABLES SECTION -------------------------#
#--------------------------------------------------------------------#
######################################################################

######################################################################
#------------------ DYNAMIC SUBSECTION - CAN MODIFY -----------------#
######################################################################

#--------------- APPLICATION NAME -------------#

APP_NAME = pattern_recognizer

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

#----------------- INSTALL DIRECTORY -----------------#

INSTALL_PATH_ARG=${INSTALL_PATH}
# If INSTALL_PATH was not set. set it to default
ifeq (${INSTALL_PATH_ARG},)
	INSTALL_PATH_ARG=./install
endif 

#----------------- PROJECT MODULES -----------------#

# List of all subdirectories in source directory
SRC_MODULES = $(shell find ${SRC} -type d 2>/dev/null)
# Adds each modules in include separately.
INC_MODULES =  $(addprefix -I , $(shell find ${INC} -type d 2>/dev/null))

#----------------- LIBRARIES MODULES -----------------#

# Variable representing comma ','
COMMA = ,

# Adds each module in lib folder to search for libs
LIB_MODULES = $(shell find ${LIB} -type d 2>/dev/null)
LIB_LINK_MODULES = $(addprefix -L , $(LIB_MODULES))

# The flags needed for ld path
LD_SHARED_PATH_FLAG = -Wl$(COMMA)-rpath
# The paths to all shared libraries
LIB_LINK_RPATH = $(addprefix ${LD_SHARED_PATH_FLAG} , $(LIB_MODULES))
# All Lib modules to include
LIB_INC_MODULES = $(addprefix -I , $(shell find ${LIB} -type d 2>/dev/null))

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
all: rel utest

# Release rule
rel: $(MAKE_EXTERNAL) info_prefix init ${APP_NAME} info_suffix

# Debug rule
debug:
	@echo 'Debug TODO'

# Unit Test rule, assumes that $(TST) has a makefile inside
utest:
	@$(MAKE) -C $(TST)

# Install rule	
install: rel init_install

################################################
#--------------- LINKER / COMPILER ------------#
################################################

#------------------ LINKER --------------------#

# Used in debug
${APP_NAME}: ${OBJECTS}
	@$(CC) -o ${BIN}/${APP_NAME} $^ $(L_FLAGS)

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

################################################
#---------------- UTILITY RULES ---------------#
################################################

# Creates all the directories of the project
init:
	@mkdir -p ${OBJ} ${BIN} ${SRC} ${LIB} ${INC} ${TST}

clean:
	$(eval OBJECTS=$(shell find ${OBJ} -name *.o))
	$(eval DEPS=$(shell find ${OBJ} -name *.d))
	$(eval TMPS=$(shell find ${OBJ} -name *.~))
	$(eval BINS=$(shell find ${BIN} -type f))
	@echo ${INFO_SEPARATOR}
	@echo
	@echo ${INFO_FILLER} "Cleaning: ${OBJ}/ ${BIN}/"
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
	@echo
	@echo "Binary Files:"
	@echo
	@$(foreach var, ${BINS}, echo ${var};)
	@echo
	@echo ${INFO_SEPARATOR}
	@echo ${INFO_SEPARATOR}
	@$(foreach var, ${OBJECTS}, rm -f ${var})
	@$(foreach var, ${DEPS}, rm -f ${var})
	@$(foreach var, ${TMPS}, rm -f ${var})
	@$(foreach var, ${BINS}, rm -f ${var})
	@$(MAKE) -C $(TST) clean

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

######################################################################
#------------------ DYNAMIC SUBSECTION - CAN MODIFY -----------------#
######################################################################

# This rule should be used to define the installation process.
# Add all requiremnt for your installation here.
# This will be ran after compilation.
init_install:
	@mkdir -p ${INSTALL_PATH_ARG}
	@echo "Installing resources"
	@cp -r ./res ${INSTALL_PATH_ARG}
	@echo "Installing scripts"
	@cp -r ./script ${INSTALL_PATH_ARG}
	@echo "Installing Libraries"
	@cp -r ${LIB} ${INSTALL_PATH_ARG}
	@cp ${BIN}/${APP_NAME} ${INSTALL_PATH_ARG}

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
