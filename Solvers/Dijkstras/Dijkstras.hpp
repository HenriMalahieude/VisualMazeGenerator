#ifndef __DIJK_SOLV_HPP__
#define __DIJK_SOLV_HPP__

#include "../../Generators/Maze.hpp"

struct DijkCellInfo{
	int distance = -1;
	pair<int, int> prevPos = {-1, -1}; //not yet set
	bool used = false;
	bool visited = false;
	bool wall = false;
};

class DijkstraSolver{
	private:
		bool finished = false;
		vector<vector<DijkCellInfo>> cellInfo = {};

	public:
		vector<pair<int, int>> visited = {};

		bool IsFinished(){ return finished; }
		void Reset(Maze &, pair<int, int> start);
		void StepSolve(Maze &, pair<int, int> end);
};

#endif