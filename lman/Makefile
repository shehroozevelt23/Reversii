XX = g++ 
CXXFLAGS = -std=c++14 -Wall -Werror=vla -MMD -g -lX11
EXEC = a4q5
OBJECTS = main.o grid.o cell.o textdisplay.o window.o graphicsdisplay.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
