CC = em++
UNUSED = --shell-file path-to/shell.html
FLAGS = -O2 -Wall -I ../include/ -L ../lib/ -lraylib -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB

all: ./maze.o
	$(CC) ../main.cpp ./maze.o -o test.html $(FLAGS)

maze.o: ../maze.cpp
	em++ ../maze.cpp -c 