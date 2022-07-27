CC = g++
FLAGS = -O2 -Wall -Wno-missing-braces -I ../include/ -L ../lib/ -lraylib -lopengl32 -lgdi32 -lwinmm

all: ./maze.o
	$(CC) ../main.cpp ./maze.o -o test.exe $(FLAGS)

release: ./maze.o
	$(CC) ../main.cpp ./maze.o -o MazeGen.exe $(FLAGS) -mwindows

maze.o: ../maze.cpp
	g++ ../maze.cpp -c 