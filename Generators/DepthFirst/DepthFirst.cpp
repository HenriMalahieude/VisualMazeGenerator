//Programmed by Henri Malahieude
#include <iostream>
#include <ctime>

#include "DepthFirst.hpp"

//using namespace std;

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

bool checkVectorForPos(vector<int> pos, const vector<vector<int>> &v){
    for (unsigned i = 0; i < v.size(); i++){
        if (pos[0] == v[i][0] && pos[1] == v[i][1]){
            return true;
        }
    }
    return false;
}

bool DepthFirstGenerator::FinishedGenerate() const{
    return isFinished;
}

void DepthFirstGenerator::Reset(Maze &m){
    if (isFinished){
        m.Clear();
        
        GetRandomPos(m, currentCell);
        visited.clear();
        stack.clear();

        isFinished = false;
    }
}

void printMaze(vector<vector<char>> &maze){
    for (unsigned iY = 0; iY < maze.size(); iY++){
        for (unsigned iX = 0; iX < maze.size(); iX++){
            cout << maze[iX][iY] << ' ';
        }
        cout << endl;
    }
}

void DepthFirstGenerator::GetRandomPos(Maze &m, vector<int> &pos){
    vector<int> randomized = {generateRandomInt(1, m.size-2), generateRandomInt(1, m.size-2)};

    if (randomized[0] % 2 == 0){
        int r = rand() % 2;
        if(r == 0){
            randomized[0]++;
        }else{
            randomized[0]--;
        }
    }

    if (randomized[1] % 2 == 0){
        int r = rand() % 2;
        if(r == 0){
            randomized[1]++;
        }else{
            randomized[1]--;
        }
    }

    clamp(randomized[0], 1, m.size-2);
    clamp(randomized[1], 1, m.size-2);

    pos = randomized;
}

void removeSelectedIndices(vector<int> selectedIndices, vector<vector<int>> &from){
    for (unsigned i = 0; i < selectedIndices.size(); i++){
        from.erase(from.begin() + selectedIndices[i] - i);
    }
}

void DepthFirstGenerator::GetPossibleDirections(Maze &m, vector<int> pos, vector<vector<int>> &directions){
    vector<vector<int>> possibleDirections = {
        {2, 0},
        {0, 2},
        {-2, 0},
        {0, -2},
    };
    vector<int> removeIndices;

    for (int d = 0; d < 4; d++){
        vector<int> newPos = {pos[0] + possibleDirections[d][0], pos[1] + possibleDirections[d][1]};

        if(newPos[0] < 1 || newPos[0] > m.size-2){
            removeIndices.push_back(d);
            continue;
        }
        if(newPos[1] < 1 || newPos[1] > m.size-2){
            removeIndices.push_back(d);
            continue;
        }

        if (checkVectorForPos(newPos, stack) || checkVectorForPos(newPos, visited)){
            removeIndices.push_back(d);
            continue;
        }
    }

    removeSelectedIndices(removeIndices, possibleDirections);

    directions = possibleDirections;
}

void DepthFirstGenerator::StepMaze(Maze &m){
    vector<vector<int>> possibleDirections;
    GetPossibleDirections(m, currentCell, possibleDirections);

    //cout << "Visited: " << visited.size() << " | In Stack: " << stack.size() << " | Directions: " << possibleDirections.size() << endl;

    if (possibleDirections.size() < 1){ //backtrack
        //cout << "Backtracking!" << endl;
        visited.push_back(currentCell);

        currentCell = stack.back();
        stack.pop_back();
    }else{ //move forward (dig out walls)
        //cout << "Moving forward!" << endl;
        vector<int> chosenDir = possibleDirections[rand() % possibleDirections.size()];
        vector<int> wallPos = {currentCell[0] + (chosenDir[0]/2), currentCell[1] + (chosenDir[1]/2)};
        
        //Remove the wall
        m.scene[wallPos[0]][wallPos[1]] = ' ';

        stack.push_back(currentCell);
        currentCell = {currentCell[0] + chosenDir[0], currentCell[1] + chosenDir[1]};
    }

    int numOfCells = (m.size-1)/2;
    if (visited.size() + stack.size() >= ((numOfCells*numOfCells) - 1)){
        isFinished = true;
    }
}