#include "Precompiled.h"
#include "GridBasedGraph.h"

using namespace AI;

void GridBasedGraph::Initialize(int columns, int rows)
{
	mNodes.clear();
	// Reserve -> Grow the capacity, but not build up for anything. Prepare the space. Size = 0
	// Resize -> Allocate specific space and put stuff in each one. Reserves capacity and size.
	mNodes.resize(columns * rows);
	mColumns = columns;
	mRows = rows;

	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			Node* node = GetNode(c, r);
			node->column = c;
			node->row = r;

			// TODO: Add the other 7 neighbours
			// It may look nicer if you have cardinal directions
			// Cardinal directions:
			// North, South, East, West
			// Northeast, Northwest, Southeast, Southwest
			node->neighbours[0] = GetNode(c, r - 1); // North
			node->neighbours[1] = GetNode(c, r + 1); // South
			node->neighbours[2] = GetNode(c + 1, r); // East
			node->neighbours[3] = GetNode(c - 1, r); // West
			node->neighbours[4] = GetNode(c + 1, r - 1); // Northeast
			node->neighbours[5] = GetNode(c - 1, r - 1); // Northwest
			node->neighbours[6] = GetNode(c + 1, r + 1); // Southeast
			node->neighbours[7] = GetNode(c - 1, r + 1); // Southwest
		}
	}

}

void GridBasedGraph::ResetSearchParams()
{
	for (auto& node : mNodes)
	{
		node.parent = nullptr;
		node.g = 0.0f;
		node.h = 0.0f;
		node.opened = false;
		node.closed = false;
	}
};