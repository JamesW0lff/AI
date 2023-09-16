#include "Dijkstra.h"

namespace
{
	auto CompareG = [](const AI::GridBasedGraph::Node* nodeA, const AI::GridBasedGraph::Node* nodeB)
	{
		return nodeA->g < nodeB->g;
	};
}

#pragma region SEARCH
bool Dijkstra::Search(GridBasedGraph& graph, int fromColumn, int fromRow, int toColumn, int toRow, function<bool(int, int)> isWalkable, 
	function<float(int, int, int, int)> getCost
)
{
	graph.ResetSearchParams();

	auto startNode = graph.GetNode(fromColumn, fromRow);
	mOpenList.push_back(startNode);
	startNode->opened = true;

	auto endNode = graph.GetNode(toColumn, toRow);

	bool pathFound = false;
	
	// while end node not reached && open list isn't empty
	while (!pathFound && !mOpenList.empty())
	{
		// select front node N from open list(this is because it is already sorted)
		GridBasedGraph::Node* nextNode = mOpenList.front();
		mOpenList.pop_front();

		// if node is end
		if (nextNode == endNode)
		{
			// found = true
			pathFound = true;
			mClosedList.push_back(nextNode);
		}
		else
		{
			int neighbours = static_cast<int>(nextNode->neighbours.size());
			float parentG = (nextNode->parent) ? nextNode->parent->g : 0.0f;

			for (int i = 0; i < neighbours; ++i) 
			{
				// if neighbour is closed or is a wall (blocked: tree, wall)
				if (!nextNode->neighbours[i] || nextNode->neighbours[i]->closed || 
					!isWalkable(nextNode->neighbours[i]->column, nextNode->neighbours[i]->row))
					continue;

				float newCost = parentG + getCost(nextNode->column, nextNode->row, nextNode->neighbours[i]->column, nextNode->neighbours[i]->row);

				// if neighbours isn't in open
				if (!nextNode->neighbours[i]->opened) 
				{
					nextNode->neighbours[i]->parent = nextNode;
					nextNode->neighbours[i]->opened = true;
					nextNode->neighbours[i]->g = newCost;

					mOpenList.push_back(nextNode->neighbours[i]);
					mOpenList.sort(CompareG);
				}
				// opened
				else if(!nextNode->neighbours[i]->closed)
				{
					if (newCost < nextNode->neighbours[i]->g)
					{
						nextNode->neighbours[i]->parent = nextNode;
						nextNode->neighbours[i]->g = newCost;
						mOpenList.sort(CompareG);
					}
				}
			}

			nextNode->closed = true;
			mClosedList.push_back(nextNode);
		}
	}

	return pathFound;
}
#pragma endregion