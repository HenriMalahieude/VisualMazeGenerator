#ifndef SOLVER_H
#define SOLVER_H

#include <vector>

using namespace std;

class GreedySolver{
    public:
        bool IsFinished() const;

        void StepSolve(vector<vector<char>> &, vector<int>, vector<int>);
        void Reset();

        vector<vector<int>> path;
        vector<vector<int>> visited;
        vector<int> currentPosition;
    private:
        bool isComplete = false;
};

#endif