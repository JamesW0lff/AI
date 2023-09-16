#pragma once

#include "AI.h"

using AI::GridBasedGraph;
using std::list;
using std::function;

class Dijkstra
{
public:
	bool Search(GridBasedGraph& graph, int fromColumn, int fromRow, int toColumn, int toRow, function<bool(int, int)> isWalkable, 
		function<float(int, int, int, int)> getCost);

	const AI::Pathing::NodeList& GetClosedList() const { return mClosedList; }

private:

	AI::Pathing::OpenList mOpenList;
	AI::Pathing::ClosedList mClosedList;

};