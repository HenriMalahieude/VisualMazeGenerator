#include <iostream>

#include "Greedy.hpp"

void GreedySolver::Reset(Maze &m){
	tried.clear();
	m.path.clear();

	finished = false;
}

bool checkVectorForPos(pair<int, int> p, const vector<pair<int, int>> &vec){
	for (unsigned i = 0; i < vec.size(); i++){
		if (p.first == vec[i].first && p.second == vec[i].second){
			return true;
		}
	}

	return false;
}

void removeSelectedIndices(vector<int> selectedIndices, vector<pair<int, int>> &from){
    for (unsigned i = 0; i < selectedIndices.size(); i++){
        from.erase(from.begin() + selectedIndices[i] - i);
    }
}

//Shamelessly Taken from DepthFirstGenerator
void GreedySolver::GetPossibleDirections(Maze &m, pair<int, int> pos, vector<pair<int, int>> &directions){
    vector<pair<int, int>> possibleDirections = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1},
    };
    vector<int> removeIndices;

    for (int d = 0; d < 4; d++){
        pair<int, int> newPos = {pos.first + possibleDirections[d].first, pos.second + possibleDirections[d].second};

        if(newPos.first < 0 || newPos.first > m.size-1){
            //cout << 1 << endl;
            removeIndices.push_back(d);
            continue;
        }
        if(newPos.second < 0 || newPos.second > m.size-1){
            //cout << 2 << endl;
            removeIndices.push_back(d);
            continue;
        }

        if (checkVectorForPos(newPos, tried) || checkVectorForPos(newPos, m.path)){
            //cout << 3 << endl;
            removeIndices.push_back(d);
            continue;
        }else if (m.scene[newPos.first][newPos.second] == '#'){
            //cout << 4 << endl;
			removeIndices.push_back(d);
		}
    }

    removeSelectedIndices(removeIndices, possibleDirections);

    directions = possibleDirections;
}

void GreedySolver::StepSolve(Maze &m, pair<int, int> s, pair<int, int> e){
    if ((int)tried.size() + (int)m.path.size() >= m.size * m.size){
        finished = true;
        return;
    }

	pair<int, int> cur =  s;
	vector<pair<int, int>> directions;

	if (m.path.size() >= 1){
        //cout << "Not choosing First" << endl;
		cur = m.path.at(m.path.size()-1);
	}

	GetPossibleDirections(m, cur, directions);
    //cout << "TOtal: " << directions.size() << endl;

    if (directions.size() > 0){
        pair<int, int> nextDir = directions[rand() % directions.size()];
        pair<int, int> nextPos = {cur.first + nextDir.first, cur.second + nextDir.second};
        if (nextPos.first == e.first && nextPos.second == e.second){
            finished = true;
            return;
        }

        m.path.push_back(nextPos);
    }else if (m.path.size() > 1){ //we need to backtrack
        tried.push_back(cur);
        m.path.erase(next(m.path.begin(), m.path.size()-1));
    }else{
        cout << "bruh" << endl;
        finished = true;
        return;
    }
    
}