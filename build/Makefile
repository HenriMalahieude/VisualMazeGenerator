CC = em++
UNUSED = --shell-file path-to/shell.html
FLAGS = -O2 -Wall -I ../include/ -L ../lib/ -lraylib -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB

all: ./DepthFirst.o
	$(CC) ../main.cpp ./DepthFirst.o -o index.html $(FLAGS)

DepthFirst.o: ../Generators/DepthFirst.cpp
	em++ ../Generators/DepthFirst.cpp -c 