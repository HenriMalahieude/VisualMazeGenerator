CC = em++
UNUSED = --shell-file path-to/shell.html
RAYLIB_PATH = C:\Users\there\OneDrive\Documents\Projects\Raylib\raylib\src
FLAGS = -O2 -Wall -I $(RAYLIB_PATH) -L ./lib/ -lraylib -s USE_GLFW=3 -s ASYNCIFY -DPLATFORM_WEB

all: ./DepthFirst.o ./Kruskal.o ./Greedy.o ./Dijkstras.o
	$(CC) ../main.cpp ./DepthFirst.o ./Kruskal.o ./Dijkstras.o ./Greedy.o -o index.html $(FLAGS)

DepthFirst.o: ../Generators/DepthFirst/DepthFirst.cpp ../Generators/DepthFirst/DepthFirst.hpp ../Generators/Maze.hpp
	$(CC) ../Generators/DepthFirst/DepthFirst.cpp -c 

Kruskal.o: ../Generators/Kruskal/Kruskal.hpp ../Generators/Kruskal/Kruskal.cpp ../Generators/Maze.hpp
	$(CC) ../Generators/Kruskal/Kruskal.cpp -c

Greedy.o: ../Solvers/Greedy/Greedy.hpp ../Solvers/Greedy/Greedy.cpp ../Generators/Maze.hpp
	$(CC) ../Solvers/Greedy/Greedy.cpp -c

Dijkstras.o: ../Solvers/Dijkstras/Dijkstras.hpp ../Solvers/Dijkstras/Dijkstras.cpp ../Generators/Maze.hpp
	$(CC) ../Solvers/Dijkstras/Dijkstras.cpp -c