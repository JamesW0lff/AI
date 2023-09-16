#pragma once

#include "GridBasedGraph.h"

// Pathing related functionality
namespace AI::Pathing
{
	using NodePath = std::vector<AI::GridBasedGraph::Node*>;
	using NodeList = std::list<GridBasedGraph::Node*>;
	using OpenList = std::list<AI::GridBasedGraph::Node*>;
	using ClosedList = std::list<AI::GridBasedGraph::Node*>;
	using Node = GridBasedGraph::Node*;

}