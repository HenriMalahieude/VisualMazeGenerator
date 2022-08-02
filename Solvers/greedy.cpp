#include "greedy.h"
#include <ctime>
#include <cstdlib>

vector<vector<int>> getConnections(vector<int> pos, vector<vector<char>> &maze){
    vector<vector<int>> connections;

    for (int x = -1; x < 2; x++){
        for (int y = -1; y < 2; y++){
            if (maze[x][y] == ' '){
                vector<int> pos = {x, y};
                connections.push_back(pos);
            }
        }
    }

    return connections;
}

bool GreedySolver::IsFinished() const{
    return isComplete;
}

void GreedySolver::Reset(){
    currentPosition.clear();
    isComplete = false;

    path.clear();
    visited.clear();
    currentPosition.clear();
}

void GreedySolver::StepSolve(vector<vector<char>> &maze, vector<int> start, vector<int> end){
    int numOfCells = (maze.size()-1) / 2;
    numOfCells *= numOfCells;

    if (currentPosition.size() < 2){
        currentPosition = start;
    }
    
    vector<int> distance = {currentPosition[0] - end[0], currentPosition[1] - end[1]};
        
    double distanceNumber = distance[0] * distance[0] + distance[1] * distance[1];
    if (distanceNumber <= 1){
        path.push_back(currentPosition);
        isComplete = true;
    }

    vector<vector<int>> possibleDirections = getConnections(currentPosition, maze);

    if (possibleDirections.size() < 1){
        visited.push_back(currentPosition);

        currentPosition = path.back();
        path.pop_back();
    }else{
        vector<int> randomDirection = possibleDirections[rand() % possibleDirections.size()];

        path.push_back(currentPosition);
        currentPosition = {currentPosition[0] + randomDirection[0], currentPosition[1] + randomDirection[1]};
    }

    if (visited.size() + path.size() >= numOfCells){
        isComplete = true;
    }
}