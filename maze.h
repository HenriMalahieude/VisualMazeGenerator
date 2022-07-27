#ifndef MAZEGEN_H
#define MAZEGEN_H
#include <vector>

using namespace std;

class MazeGenerator{
    public:
        //General Info
        vector<vector<char>> maze;
        vector<int> currentCell = {1, 1};

        MazeGenerator(int);

        bool FinishedGenerate() const;

        void ResetMaze();
        void ClearMaze();
        void StepMaze();

    private:
        void GetRandomPos(vector<int> &pos);
        void GetPossibleDirections(vector<int> pos, vector<vector<int>> &directions);
        void CreateRandomEntrances();

        int mazeSize;
        bool isFinished;

        //Creation Info
        vector<vector<int>> stack;
        vector<vector<int>> visited;
};
#endif