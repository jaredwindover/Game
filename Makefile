#DIRECTORIES
CURDIR		= $(shell pwd)
OBJDIR		= obj/
SRCDIR		= src/
OUTDIR		= out/

#UTILITIES
RM		= gvfs-trash

#COMPILER
CXX		= g++

#COMPILER FLAGS
CXXFLAGS	= -Wall -MMD -std=c++11

#FINAL EXECUTABLE NAME
EXEC		= ${OUTDIR}runme.out

#TEST EXECUTABLE NAME
TEST		= ${OUTDIR}run-tests.out

#MAIN OBJECTS
OBJLIST		= Background.o\
		  Game.o\
		  Terrain.o\
		  Utility.o\
		  Player.o\

OBJS		= ${patsubst %.o, ${OBJDIR}%.o, ${OBJLIST}}

#TEST OBJECTS
TESTLIST	= test.o\

TESTS		= ${patsubst %.o, ${OBJDIR}%.o, ${TESTLIST}}

#MAIN OBJECT
MAIN		= ${OBJDIR}main.o

#MAIN TEST OBJECT
TESTMAIN	= ${OBJDIR}gtest_main.o

#DEBUG OBJECTS
DOBJS		= ${OBJS:.o=_debug.o}

#DEPENDENCY FILES
DEPENDS		= ${OBJS:.o=.d} ${TESTS:.o=.d}

#LINKER FLAGS
LDFLAGS 	= -lsfml-system -lsfml-window -lsfml-graphics -lgtest

#FLAGS FOR TEST COMPILATION
TESTFLAGS	= -Wno-unused-result

#DEBUG
ifdef DEBUG

#COMPILER FLAGS
CXXFLAGS	+= -g -O0 -DDEBUG

#DEBUG EXECUTABLE NAME
EXEC		= runme-debug.out

#USE DEBUG OBJECTS
OBJECTS		= ${DOBJS}

else #|DEBUG

#USE NORMAL OBJECTS
OBJECTS		= ${OBJS}

endif #/DEBUG

main: ${EXEC}

run: ${EXEC}
	${EXEC}

#BUILD MAIN EXECUTABLE
${EXEC}: ${OBJECTS} ${MAIN}
	echo ${OBJS}
	${CXX} ${CXXFLAGS} ${OBJECTS} ${MAIN} -o ${EXEC} ${LDFLAGS}

#BUILD TEST EXECUTABLE
${TEST}: ${OBJECTS} ${TESTS} ${TESTMAIN}
	${CXX} ${CXXFLAGS} ${TESTFLAGS} ${OBJECTS} ${TESTS} ${TESTMAIN} -o ${TEST} ${LDFLAGS}

#IF BUILDING OBJECTS OR TESTS BUILD DIRECTORY FIRST
${OBJECTS} ${TESTS} : | ${OBJDIR}

#BUILD OBJECT DIRECTORY
${OBJDIR}:
	@mkdir -p $@

#BUILD OBJECTS
${OBJDIR}%.o : ${SRCDIR}%.cc
	${CXX} -c ${CXXFLAGS} $< -o $@

#BUILD DEBUG OBJECTS
${OBJDIR}%_debug.o: ${SRCDIR}%.cc
	${CXX} -c ${CXXFLAGS} $< -o $@

#USE DEPENDENCY INFORMATION
-include ${DEPENDS}

#BULID AND RUN TEST
test: ${TEST}
	${TEST}

#RUN REGARDLESS
.PHONY: clean clear

#CLEAN DIRECTORY
clean:
	@sh ${SRCDIR}clean.sh "${RM} -f ${OBJDIR}* **/*~"
#CLEAR EXECUTABLES
clear:
	@${RM} -f ${OUTDIR}*
