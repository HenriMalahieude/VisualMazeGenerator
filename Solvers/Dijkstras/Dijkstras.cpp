#include "Dijkstras.hpp"

#include <iostream>

template<typename T>
void removeSelectedIndices(vector<int> selectedIndices, vector<T> &from){
    for (unsigned i = 0; i < selectedIndices.size(); i++){
        from.erase(from.begin() + selectedIndices[i] - i);
    }
}

void GetValidDirections2_Dijk(Maze &m, vector<pair<int, int>> &dirs, pair<int, int> pos){
	vector<pair<int, int>> possibleDirections = {
        {1, 0},
        {0, 1},
        {-1, 0},
        {0, -1},
    };
    vector<int> removeIndices;

    for (int d = 0; d < 4; d++){
        pair<int, int> newPos = {pos.first + possibleDirections[d].first, pos.second + possibleDirections[d].second};
		pair<int, int> newPos2 = {pos.first + possibleDirections[d].first*2, pos.second + possibleDirections[d].second*2};

		//Check within bounds
        if(newPos.first < 0 || newPos.first > m.size-1 || newPos.second < 0 || newPos.second > m.size-1){
            //cout << 1 << endl;
            removeIndices.push_back(d);
            continue;
        }

		if(newPos2.first < 0 || newPos2.first > m.size-1 || newPos2.second < 0 || newPos2.second > m.size-1){
            //cout << 1 << endl;
            removeIndices.push_back(d);
            continue;
        }

		//Check no wall in way
		if (m.scene[newPos.first][newPos.second] == '#'){
			removeIndices.push_back(d);
		}
	}

	removeSelectedIndices(removeIndices, possibleDirections);
	dirs = possibleDirections;
}

//Note: Source is in (X, Y) format. Horizontal first, vertical second.
void DijkstraSolver::Reset(Maze &m, pair<int, int> s){
	finished = false;

	cellInfo.clear();
	visited.clear();
	m.path.clear();

	for (unsigned int x = 0; x < m.size; x++){
		cellInfo.push_back(vector<DijkCellInfo>(0));

		for (unsigned int y = 0; y < m.size; y++){
			cellInfo[x].push_back(DijkCellInfo{m.size * m.size, {-1, -1}, false, false, x % 2 == 0 || y % 2 == 0});
			if (x == s.first && y == s.second){
				cellInfo[x][y].distance = 0; //Set source to zero
				cellInfo[x][y].prevPos = {-5, -5};
				cellInfo[x][y].visited = true;
			}
		}
	}

	visited.push_back(s); //put source in "visited" list
}

pair<int, int> GetInBetweenPos(vector<vector<DijkCellInfo>> &cellInfo, pair<int, int> pos){
	if (cellInfo[pos.first][pos.second].prevPos.first >= 0){
		pair<int, int> prevClos = cellInfo[pos.first][pos.second].prevPos;
		pair<int, int> dir = {pos.first - prevClos.first, pos.second - prevClos.second};
		return {prevClos.first + (dir.first / 2), prevClos.second + (dir.second / 2)};
	}

	return {-1, -1};
}

//Note: Source is in (X, Y) format. Horizontal first, vertical second.
void DijkstraSolver::StepSolve(Maze &m, pair<int, int> e){
	//First: Find the next point that has the closest distance that hasn't been used
	int nextClosestDist = m.size * m.size;
	pair<int, int> nextCloses = {-1, -1};

	for (unsigned int x = 0; x < cellInfo.size(); x++){
		for (unsigned y = 0; y < cellInfo.size(); y++){
			DijkCellInfo info = cellInfo[x][y];
			if (!info.wall && !info.used && info.visited && info.distance < nextClosestDist){
				nextCloses.first = x; nextCloses.second = y;
				nextClosestDist = info.distance;
			}
		}
	}

	//Next: We end if...
	if (nextCloses.first < 0 || nextCloses.second < 0){ //if we already visited it, or none exist
		finished = true;
		return; //with no path
	}else if (nextCloses == e){ //if we've found the end position
		DijkCellInfo reference = cellInfo[e.first][e.second];
		
		m.path.push_back({e.first, e.second});
		pair<int, int> inBetween = GetInBetweenPos(cellInfo, reference.prevPos);

		if (inBetween.first >= 0){
			cout << e.first << ", " << e.second << endl;
			cout << inBetween.first << ", " << inBetween.second << endl;
			cout << reference.prevPos.first << ", " << reference.prevPos.second << endl;
			m.path.push_back(inBetween);
		}

		while(reference.prevPos.first > 0 && reference.prevPos.second > 0){ //we could compare all of it but no need
			m.path.push_back({reference.prevPos.first, reference.prevPos.second});
			pair<int, int> inBetween = GetInBetweenPos(cellInfo, reference.prevPos);

			if (inBetween.first >= 0){
				m.path.push_back(inBetween);
			}

			reference = cellInfo[reference.prevPos.first][reference.prevPos.second];
		}

		finished = true;
		return;
	}

	//Otherwise: Now that we have node, go through each neighbor of node: determine distance and set their previous node.
	vector<pair<int, int>> dirToGo = {};
	GetValidDirections2_Dijk(m, dirToGo, nextCloses);

	for (unsigned i = 0; i < dirToGo.size(); i++){
		pair<int, int> sumNext = {nextCloses.first + (dirToGo[i].first*2), nextCloses.second + (dirToGo[i].second*2)};

		if (!cellInfo[sumNext.first][sumNext.second].visited){
			cellInfo[sumNext.first][sumNext.second].distance = cellInfo[nextCloses.first][nextCloses.second].distance + 1;
			cellInfo[sumNext.first][sumNext.second].prevPos = nextCloses;
			cellInfo[sumNext.first][sumNext.second].visited = true;
		}
	}

	//Lastly: Add it to visited, add the connecting destroyed wall to visited, and set it as used
	visited.push_back(nextCloses);
	pair<int, int> inBetween = GetInBetweenPos(cellInfo, nextCloses);
	if (inBetween.first >= 0){
		visited.push_back(inBetween);
	}

	cellInfo[nextCloses.first][nextCloses.second].used = true;
}
