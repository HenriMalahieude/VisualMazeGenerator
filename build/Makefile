CC = em++
UNUSED = --shell-file path-to/shell.html
FLAGS = -O2 -Wall -I ./include/ -L ./lib/ -lraylib -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB

all: ./DepthFirst.o ./Kruskal.o
	$(CC) ../main.cpp ./DepthFirst.o ./Kruskal.o -o index.html $(FLAGS)

DepthFirst.o: ../Generators/DepthFirst.cpp ../Generators/Maze.hpp
	$(CC) ../Generators/DepthFirst.cpp -c 

Kruskal.o: ../Generators/Kruskal.cpp ../Generators/Maze.hpp
	$(CC) ../Generators/Kruskal.cpp -c