#pragma once

#include "AI.h"

using AI::GridBasedGraph;
using std::list;
using std::function;

class AStar
{
public:
	bool Search(GridBasedGraph& graph, int fromColumn, int fromRow, int toColumn, int toRow, function<bool(int, int)> isWalkable,
		function<float(int, int, int, int)> getCost, function<float(int, int, int, int)> getDistance);

	const AI::Pathing::NodeList& GetClosedList() const { return mClosedList; }

private:

	AI::Pathing::OpenList mOpenList;
	AI::Pathing::ClosedList mClosedList;

};

// http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html