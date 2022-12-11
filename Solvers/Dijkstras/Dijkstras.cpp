#include "Dijkstras.hpp"

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

		//Check within bounds
        if(newPos.first < 0 || newPos.first > m.size-1 || newPos.second < 0 || newPos.second > m.size-1){
            //cout << 1 << endl;
            removeIndices.push_back(d);
            continue;
        }

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
	lastClosest = {-2, -2};

	cellInfo.clear();
	visited.clear();
	m.path.clear();

	for (unsigned int x = 0; x < m.size; x++){
		cellInfo.push_back(vector<DijkCellInfo>(0));

		for (unsigned int y = 0; y < m.size; y++){
			cellInfo[x].push_back(DijkCellInfo{m.size * m.size, {0, 0}, x % 2 == 0 || y % 2 == 0});
			if (x == s.first && y == s.second){
				cellInfo[x][y].distance = 0; //Set source to zero
				cellInfo[x][y].prevPos = {-5, -5};
			}
		}
	}

	visited.push(s); //put source in "visited" list
}

//Note: Source is in (X, Y) format. Horizontal first, vertical second.
void DijkstraSolver::StepSolve(Maze &m, pair<int, int> e){
	//First: Find the next point that has the closest distance that hasn't been used
	int nextClosestDist = m.size * m.size;
	pair<int, int> nextCloses = {-1, -1};

	for (unsigned int x = 0; x < cellInfo.size(); x++){
		for (unsigned y = 0; y < cellInfo.size(); y++){
			DijkCellInfo info = cellInfo[x][y];
			if (!info.used && info.distance < nextClosestDist){
				nextCloses.first = x; nextCloses.second = y;
				nextClosestDist = info.distance;
			}
		}
	}

	//Next: We end if...
	if (nextCloses == lastClosest || nextCloses.first == -1){ //if we already visited it, or none exist
		finished = true;
		return; //with no path
	}else if (nextCloses == e){ //if we've found the end position
		DijkCellInfo reference = cellInfo[e.first][e.second];
		m.path.push_back({e.first, e.second});
		while(reference.prevPos.first != -5){ //we could compare all of it but no need
			m.path.push_back({reference.prevPos.first, reference.prevPos.second});
			reference = cellInfo[reference.prevPos.first][reference.prevPos.second];
		}

		finished = true;
		return;
	}

	//Otherwise: Now that we have node, go through each neighbor of node: determine distance and set their previous node.
	vector<pair<int, int>> dirToGo = {};
	GetValidDirections2_Dijk(m, dirsToGo, nextCloses);
	for (unsigned i = 0; i < dirToGo.size(); i++){
		pair<int, int> sumNext = {nextCloses.first + (dirsToGo[i].first*2), nextCloses.second + (dirsToGo[i].second*2)};
		cellInfo[sumNext.first][sumNext.second].distance = cellInfo[nextCloses.first][nextCloses.second] + 1;
		cellInfo[sumNext.first][sumNext.second].prevPos = nextCloses;
	}

	//Lastly: Prepare for the next step
	visited.push_back(nextCloses);
	cellInfo[nextCloses.first][nextCloses.second].used = true;
	lastClosest = nextCloses;
}
