#ifndef __KRUSKAL_G_H_
#define __KRUSKAL_G_H_

#include "../Maze.hpp"

struct Cell{
    int x = -1, y;
    int seed;
    int collapsedDirections = 0;
};

class KruskalGenerator{
    private:
        vector<Cell> seeds;
        vector<Cell> used;
        bool isFinished = true;

        int UniqueSeeds();
        void CollapseSeedGroups(int from, int to);
        void GetNextDirection(const Maze&, pair<int, int>, pair<int, int> &possible);
        Cell* GetCellAtPos(pair<int, int>);
    public:
        KruskalGenerator(){};
        bool Finished() const {return isFinished;}

        void Reset(Maze&);
        void StepMaze(Maze&);

};

#endif