CXX		= g++
CXXFLAGS	= -Wall -MMD -std=c++11
EXEC		= runme.out
OBJS 		= 	Background.o\
			Game.o\
			main.o\
			Terrain.o\
			Utility.o\
			Player.o\

DOBJS		= ${OBJS:.o=_debug.o}

DEPENDS		= ${OBJS:.o=.d}
CD		= cd
CURDIR		= $(shell pwd)
SUITEDIR	= ${CURDIR}/tests/
SUITE		= GameSuite.txt 
ZIPNAME 	= game
SUITEFLAGS	= 
LDFLAGS 	= -lsfml-system -lsfml-window -lsfml-graphics

ifdef DEBUG
CXXFLAGS	+= -g -O0 -DDEBUG
EXEC		= runme-debug.out
SUITEFLAGS	+= -v -d
OBJECTS		= ${DOBJS}
else
OBJECTS		= ${OBJS}
endif

ifdef MEM
SUITEFLAGS	+= -m
endif


${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} ${LDFLAGS}

%_debug.o: %.cc
	${CXX} -c ${CXXFLAGS} $< -o $@

-include ${DEPENDS}

.PHONY: clean test submit

test:	${EXEC}
	@${CD} ${SUITEDIR}; \
	echo "Beginning Test"; \
	runSuite ${SUITEFLAGS} ${SUITE} ${CURDIR}/${EXEC}; \
	echo "Finished Test"; \

clean:
	rm -f ${OBJS} ${DOBJS} ${DEPENDS} ${DEPENDS:.d=_debug.d} *~

submit:
	zip ${ZIPNAME} *.cc *.h Makefile
