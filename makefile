#######################################################
#                                                     #
#						      #
# This makefile shall invoke all modules' makefiles   #
#						      #
#						      #
#######################################################

all: CREATE_BIN GUI PATTERN_RECOGNIZER

CREATE_BIN:
	mkdir -p bin

GUI:
	cd gui && ant && cp ConfigurationPanel.jar ../bin

PATTERN_RECOGNIZER:
	cd pattern_recognizer && make && cp ./bin/pattern_recognizer ../bin
