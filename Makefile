CURRENT_DIR = $(shell pwd)

INCLUDES = -I$(CURRENT_DIR)/include

CC = gcc
CXX = g++

LIBS = -lglfw -lassimp -ldl
CXXFLAGS = -Wall -std=c++11 -g

OBJS = Main.o modelLoader.o camera.o  glad.o

Z-Buffer: $(OBJS)
	${CXX} ${CXXFLAGS} ${INCLUDES} ${OBJS} -o $@ ${LIBS}

clean:
	-rm -f *.o core *.core

.cpp.o:
	${CXX} ${CXXFLAGS} ${INCLUDES} -c -o $@ $<

.c.o:
	${CC} ${INCLUDES} -c -o $@ $<