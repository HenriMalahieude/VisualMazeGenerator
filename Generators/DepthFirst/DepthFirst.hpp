#ifndef __DEPTH_1ST_H_
#define __DEPTH_1ST_H_

#include "../Maze.hpp"

class DepthFirstGenerator{
    private:
        vector<vector<int>> stack;
        vector<vector<int>> visited;

        void GetRandomPos(Maze &m, vector<int> &pos);
        void GetPossibleDirections(Maze &m, vector<int> pos, vector<vector<int>> &directions);
        bool isFinished = true;

    public:
        vector<int> currentCell = {1, 1};

        DepthFirstGenerator() {};

        bool FinishedGenerate() const;

        void Reset(Maze&);
        void StepMaze(Maze&);
};

#endif