#ifndef __DIJK_SOLV_HPP__
#define __DIJK_SOLV_HPP__

#include "../../Generators/Maze.hpp"

struct DijkCellInfo{
	int distance = -1;
	pair<int, int> prevPos = {-1, -1}; //not yet set
	bool used = false;
};

class DijkstraSolver{
	private:
		bool finished = false;
		pair<int, int> lastClosest = {-2, -2};
		vector<vector<DijkCellInfo>> cellInfo = {};

	public:
		vector<pair<int, int>> visited = {};

		bool IsFinished(){ return finished; }
		bool Reset(Maze &);
		void StepSolve(Maze &);
};

#endif