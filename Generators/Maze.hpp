#ifndef MAZEGEN_H
#define MAZEGEN_H
#include <vector>
#include <cstdlib>

using namespace std;

enum Generator {NONE = 0, DEPTH_FIRST, KRUSKAL};

struct Maze{
    int size;
    vector<vector<char>> scene = {};

    void Clear(){
        scene.clear();
        for (int iX = 0; iX < size; iX++){
            scene.push_back(vector<char>(0));

            for (int iY = 0; iY < size; iY++){
                if (iY % 2 == 0 || iX % 2 == 0){
                    //maze[iX][iY] = '#';
                    scene[iX].push_back('#');
                }else{
                    scene[iX].push_back(' ');
                }
            }
        }

        scene[0][1] = ' '; //Standard Exits, could rewrite my random exits code but too lazy
        scene[size -1][size - 2] = ' ';
    };
};

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