#include "BFS.h"

// WEEK 07 - min 48

#pragma region SEARCH
bool BFS::Search(GridBasedGraph& graph, int fromColumn, int fromRow, int toColumn, int toRow, function<bool(int, int)> isBlocked)
{
	bool foundPath = false;

	// Make sure our graph is clean
	graph.ResetSearchParams();

	auto startNode = graph.GetNode(fromColumn, fromRow);
	
	mOpenList.push_back(startNode);

	startNode->opened = true;

	auto endNode = graph.GetNode(toColumn, toRow);

	while (!foundPath && !mOpenList.empty())
	{
		GridBasedGraph::Node* nextNode = mOpenList.front();
		mOpenList.pop_front();

		if (nextNode == endNode)
		{
			foundPath = true;
			mClosedList.push_back(nextNode);
			break;
		}
		else
		{
			int neighbors = static_cast<int>(nextNode->neighbours.size());
			for (int i = 0; i < neighbors; ++i) {
				if (!nextNode->neighbours[i] || isBlocked(nextNode->neighbours[i]->column, nextNode->neighbours[i]->row))
					continue;

				if (!(nextNode->neighbours[i]->opened || nextNode->neighbours[i]->closed)) 
				{
					nextNode->neighbours[i]->parent = nextNode;
					nextNode->neighbours[i]->opened = true;
					mOpenList.push_back(nextNode->neighbours[i]);
				}

			}
			nextNode->closed = true;
			mClosedList.push_back(nextNode);
		}
	}

	return foundPath;
}
#pragma endregion