#ifndef __SOLV_GREEDY_
#define __SOLV_GREEDY_

#include "../../Generators/Maze.hpp"

class GreedySolver{
	private:
		bool finished = true;
		void GetPossibleDirections(Maze &, pair<int, int>, vector<pair<int, int>> &);

	public:
		//First = x, Second = y
		vector<pair<int, int>> tried = {};

		bool IsFinished() const {return finished;}
		void Reset(Maze &);
		void StepSolve(Maze &m, pair<int, int>, pair<int, int>);
};

#endif