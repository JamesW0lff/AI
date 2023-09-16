#pragma once

#include "AI.h"

using AI::GridBasedGraph;
using std::list;
using std::function;

class DFS
{
	public:
		bool Search(GridBasedGraph& graph, int fromColumn, int fromRow, int toColumn, int toRow, function<bool(int, int)> isBlocked);

		const AI::Pathing::NodeList& GetClosedList() const { return mClosedList; }

	private:

		AI::Pathing::OpenList mOpenList;
		AI::Pathing::ClosedList mClosedList;
};