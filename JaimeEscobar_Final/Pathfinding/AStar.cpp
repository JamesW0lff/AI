#include "AStar.h"

#pragma region SEARCH
bool AStar::Search(GridBasedGraph& graph, int fromColumn, int fromRow, int toColumn, int toRow, function<bool(int, int)> isWalkable,
	function<float(int, int, int, int)> getCost, function<float(int, int, int, int)> getDistance)
{
	graph.ResetSearchParams();

	auto startNode = graph.GetNode(fromColumn, fromRow);
	mOpenList.push_back(startNode);
	startNode->opened = true;

	auto endNode = graph.GetNode(toColumn, toRow);

	bool pathFound = false;

	while (!pathFound && !mOpenList.empty())
	{
		auto nextNode = mOpenList.front();
		mOpenList.pop_front();


		if (nextNode == endNode)
		{
			pathFound = true;
		}
		else
		{
			for (int i = 0; i < 8; i++)
			{
				if (nextNode->neighbours[i] != nullptr)
				{
					if (!isWalkable(nextNode->neighbours[i]->column, nextNode->neighbours[i]->row))
						continue;

					nextNode->neighbours[i]->h = getDistance(nextNode->neighbours[i]->column, nextNode->neighbours[i]->row, endNode->column, endNode->row);
					auto NewG = nextNode->g + getCost(nextNode->column, nextNode->row, nextNode->neighbours[i]->column, nextNode->neighbours[i]->row);
					float total = NewG + nextNode->neighbours[i]->h;
					if (!nextNode->neighbours[i]->opened)
					{
						if (!mOpenList.empty())
						{
							for (auto iter = mOpenList.begin(); iter != mOpenList.end(); iter++)
							{
								if (total < ((*iter)->g + (*iter)->h))
								{
									nextNode->neighbours[i]->opened = true;
									nextNode->neighbours[i]->parent = nextNode;
									nextNode->neighbours[i]->g = NewG;
									mOpenList.insert(iter, nextNode->neighbours[i]);
									break;
								}
							}
							nextNode->neighbours[i]->opened = true;
							nextNode->neighbours[i]->parent = nextNode;
							nextNode->neighbours[i]->g = NewG;
							mOpenList.push_back(nextNode->neighbours[i]);
						}
						else
						{
							nextNode->neighbours[i]->opened = true;
							nextNode->neighbours[i]->parent = nextNode;
							nextNode->neighbours[i]->g = NewG;
							mOpenList.push_back(nextNode->neighbours[i]);
						}
					}
					else if (!nextNode->neighbours[i]->closed)
					{

						if (total < nextNode->neighbours[i]->g + nextNode->neighbours[i]->h) //<== old g
						{
							nextNode->neighbours[i]->g = NewG;
							nextNode->neighbours[i]->parent = nextNode;
							mOpenList.insert(mOpenList.begin(), nextNode->neighbours[i]);
							mOpenList.pop_back();
						}
					}
				}
			}
		}
		mClosedList.push_back(nextNode);
		nextNode->closed = true;
	}

	return pathFound;
}
#pragma endregion