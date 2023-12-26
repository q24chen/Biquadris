CXX = g++-11
CXXFLAGS = -std=c++20 -Wall -MMD -Werror=vla -g
SRCS = $(shell find . -type f -name "*.cc")
OBJECTS = ${SRCS:.cc=.o}
DEPENDS = ${OBJECTS:.o=.d}
EXEC = biquadris

.PHONY: all clean

all: ${EXEC}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} $^ -o $@ -lX11

-include ${DEPENDS}

clean:
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
	