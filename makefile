#######################################################
#                                                     #
#						      #
# This makefile shall invoke all modules' makefiles   #
#						      #
#						      #
#######################################################

JAVA_JDK=/usr/lib/jvm/java-8-oracle

all: CREATE_BIN GUI PATTERN_RECOGNIZER

CREATE_BIN:
	mkdir -p bin

GUI:
	cd gui && ant -DJAVA_HOME="${JAVA_JDK}" && cp ConfigurationPanel.jar ../bin

PATTERN_RECOGNIZER:
	cd pattern_recognizer && make && cp ./bin/pattern_recognizer ../bin
