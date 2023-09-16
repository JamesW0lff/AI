#pragma once

#include "AI.h"

using AI::GridBasedGraph;
using std::list;
using std::function;

class BFS
{
	public:
		
		bool Search(GridBasedGraph& graph, int fromColumn, int fromRow, int toColumn, int toRow, function<bool(int, int)> isBlocked);

		const AI::Pathing::NodeList& GetClosedList() const { return mClosedList; }

	private:
		
		AI::Pathing::OpenList mOpenList;
		AI::Pathing::ClosedList mClosedList;

};

// https://stackoverflow.com/questions/20353210/usage-and-syntax-of-stdfunction#:~:text=std::function%20is%20a%20type%20erasure%20object.%20That%20means,operator%20()%20--%20the%20'function%20like%20call%20operator'.
