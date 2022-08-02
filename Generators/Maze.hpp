#ifndef MAZEGEN_H
#define MAZEGEN_H
#include <vector>

using namespace std;

struct Maze{
    int size;
    vector<vector<char>> scene;

    void Clear(){
        for (unsigned iX = 0; iX < size; iX++){
            scene.push_back(vector<char>(0));

            for (unsigned iY = 0; iY < size; iY++){
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
        bool isFinished;

    public:
        vector<int> currentCell = {1, 1};

        DepthFirstGenerator() {};

        bool FinishedGenerate() const;

        void Reset(Maze&);
        void StepMaze(Maze&);
};

class KruskalGenerator{
    private:
        vector<vector<int>> cellSeeds;
        bool isFinished;

    public:
        void Reset(Maze&);
        void StepMaze(Maze&);

};

//Global Functions
void clamp(int &value, int min, int max){
    if (min > max){
        return;
    }

    if (value > max){
        value = max;
    }else if(value < min){
        value = min;
    }
}

int generateRandomInt(int low, int high){
    return low + rand() % (high - low + 1);
}

#endif