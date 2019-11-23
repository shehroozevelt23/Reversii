CXX = g++
CXXFLAGS = -std=c++14 -Wall -Werror -g -MMD -Werror=vla
EXEC = a4q5
OBJECTS = main.o cell.o grid.o textdisplay.o window.o graphicsdisplay.o 
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lX11 -L/usr/X11/lib -I/usr/X11/include


-include ${DEPENDS}

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
.PHONY: clean
