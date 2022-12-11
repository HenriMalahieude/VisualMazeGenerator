#ifndef MAZEGEN_H
#define MAZEGEN_H

#include <vector>
#include <cstdlib>

using namespace std;

void removeSelectedIndices(vector<int> selectedIndices, vector<pair<int, int>> &from);

struct Maze{
    int size;
    vector<vector<char>> scene = {};
    vector<pair<int, int>> path = {};

    void Clear(){
        scene.clear();
        path.clear();
        for (int iX = 0; iX < size; iX++){
            scene.push_back(vector<char>(0));

            for (int iY = 0; iY < size; iY++){
                if (iY % 2 == 0 || iX % 2 == 0){
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

#endif