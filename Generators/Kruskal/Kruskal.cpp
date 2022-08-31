#include "Kruskal.hpp"
#include <utility>
#include <iostream>

int KruskalGenerator::UniqueSeeds(){
    vector<int> uniques(0);
    bool (*check)(int s, vector<int> &u) = [](int s, vector<int> &u){
        for (unsigned i = 0; i < u.size(); i++){
            if (u.at(i) == s){
                return false;
            }
        }
        return true;
    };

    for (unsigned i = 0; i < seeds.size(); i++){
        if (check(seeds.at(i).seed, uniques)){
            uniques.push_back(seeds.at(i).seed);
        }
    }

    for (unsigned i = 0; i < used.size(); i++){
        if (check(used.at(i).seed, uniques)){
            uniques.push_back(used.at(i).seed);
        }
    }

    return uniques.size();
}

Cell* KruskalGenerator::GetCellAtPos(pair<int, int> pos){
    for (unsigned x = 0; x < seeds.size(); x++){
        if (seeds[x].x == pos.first && seeds[x].y == pos.second){
            return &seeds[x];
        }
    }

    for (unsigned x = 0; x < used.size(); x++){
        if (used[x].x == pos.first && used[x].y == pos.second){
            return &used[x];
        }
    }

    return nullptr;
}

void KruskalGenerator::CollapseSeedGroups(int from, int to){
    for (unsigned x = 0; x < seeds.size(); x++){
        if (seeds[x].seed == from){
            seeds[x].seed = to;
        }
    }

    for (unsigned x = 0; x < used.size(); x++){
        if (used[x].seed == from){
            used[x].seed = to;
        }
    }
}

void KruskalGenerator::GetNextDirection(const Maze &m, pair<int, int> pos, pair<int, int> &possible){
    pair<int, int> pDirs[4] = {
        {0, 1}, {0, -1},
        {1, 0}, {-1, 0},
    };

    vector<int> pIndex = {};

    for (int i = 0; i < 4; i++){
        pair<int, int> nPos = {pDirs[i].first*2 + pos.first, pDirs[i].second*2 + pos.second};
        
        //If not into the edge of the map
        if (nPos.first > 0 && nPos.second > 0 && nPos.first < (m.size-1) && nPos.second < (m.size-1)){
            Cell *nCell = GetCellAtPos(nPos), *oCell = GetCellAtPos(pos);
            //If not the same cell or nullptr
            if (nCell != oCell && nCell != nullptr && oCell != nullptr){
                if (nCell->seed != oCell->seed){
                    pIndex.push_back(i);
                }else{ //Collapse seed, cannot travel in that direction anymore
                    //oCell->collapsedDirections++;
                }
            }
        }
    }

    if (pIndex.size() >= 1){
        possible = pDirs[pIndex[rand() % pIndex.size()]];
    }
}

void KruskalGenerator::Reset(Maze &m){
    if (isFinished){
        m.Clear();
        
        seeds.clear();
        for (int x = 0; x < m.size; x++){
            for(int y = 0; y < m.size; y++){
                if (x % 2 != 0 && y % 2 != 0){
                    int sd = (0.5)*(x+y)*(x+y+1)+y; //Cantor (From Wikipedia: The Free Encyclopedia)
                    seeds.push_back(Cell{x, y, sd, 0}); 
                }
            }
        }

        isFinished = false;
    }
}

void KruskalGenerator::StepMaze(Maze &m){
    if (!isFinished){
        int randCellIndex = seeds.size() > 0 ? rand() % seeds.size() : 0; //Get a new cell
        Cell rCell = seeds[randCellIndex];
        while (rCell.collapsedDirections > 3 && seeds.size() > 0){ //Ensure that the cell has directions
            vector<Cell>::iterator it = seeds.begin();
            advance(it, randCellIndex);
            used.push_back(*it);
            seeds.erase(it);

            randCellIndex = seeds.size() > 0 ? rand() % seeds.size() : 0;
            rCell = seeds[randCellIndex]; //find a new cell
        }

        if (seeds.size() <= 1 || UniqueSeeds() < 2){ //All Groups of Cells have been joined together, therefore we are done.
            //TODO: Ensure that there is only one seed, if not then find the seed with the least amount of cells and then put them back in the seeds list
            isFinished = true; //and we are done
            return;
        }

        pair<int, int> nextPos = {rCell.x, rCell.y};
        pair<int, int> nextDirection = {-1, -1};
        GetNextDirection(m, nextPos, nextDirection); //Get next directions so that it doesn't go out-of-bounds, and into its own seed

        if (nextDirection.first != nextDirection.second){ //If there are no directions possible
            pair<int, int> wallPos = {nextPos.first + nextDirection.first, nextPos.second + nextDirection.second}; //get wall pos
            pair<int, int> dirPos = {nextPos.first + nextDirection.first*2, nextPos.second + nextDirection.second*2}; //get opponent cell

            Cell *oCell, *nCell;
            oCell = GetCellAtPos(nextPos);
            nCell = GetCellAtPos(dirPos);

            if (oCell != nCell && oCell != nullptr && nCell != nullptr){
                m.scene[wallPos.first][wallPos.second] = ' '; //delete wall
                CollapseSeedGroups(nCell->seed, oCell->seed); //Collapse the seed group
                seeds[randCellIndex].collapsedDirections++;
            }
        }else{
            seeds[randCellIndex].collapsedDirections++;
        }
    }
}