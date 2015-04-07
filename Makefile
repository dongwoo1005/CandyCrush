#variables
CXX = g++
CXXFLAGS = -Wall -MMD
EXEC = ss5k
OBJECTS = main.o squareswapper.o level.o lv0.o lv1.o lv2.o lv3.o board.o square.o basic.o lateral.o upright.o unstable.o psychedelic.o textdisplay.o window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -lX11 -lncurses -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
