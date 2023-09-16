#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

#include "TileMap.h"
#include "BFS.h"
#include "DFS.h"
#include "Dijkstra.h"
#include "AStar.h"


// Jaime Escobar Sánchez
// Artificial Intelligence

#pragma region GLOBALS
TileMap tileMap;

AI::GridBasedGraph graph;

AI::Pathing::NodePath path;
AI::Pathing::OpenList openList;
AI::Pathing::ClosedList closedList;

int startX = 0, startY = 0;
int endX = 0, endY = 0;

X::TextureId mBatmanTextureId = 0;
X::TextureId mJokerTextureId = 0;

X::Math::Vector2 mBatmanPosition = { 0.0f, 0.0f };
X::Math::Vector2 mJokerPosition = { 0.0f, 0.0f };
#pragma endregion

#pragma region LAMBDAS
#pragma region GET POSITION
X::Math::Vector2 GetPosition(int column, int row)
{
	return	{
		(column + 0.5f) * tileMap.GetTileWidth(),
		(row + 0.5f) * tileMap.GetTileHeight()
	};
}

X::Math::Vector2 GetPosition(const AI::Pathing::Node node)
{
	return GetPosition(node->column, node->row);
}
#pragma endregion

// BFS // DFS
#pragma region IS BLOCKED
// Anatomy of a C++ Lambda
// [<capture list>](parameter list)
// {
// <function body>
// };
auto isBlocked = [](int column, int row)
{
	return tileMap.IsBlocked(column, row);
};
#pragma endregion

// DIJKSTRA
#pragma region IS WALKABLE
auto isWalkable = [](int toColumn, int toRow)
{
	return tileMap.IsWalkable(toColumn, toRow);
};
#pragma endregion

// DIJKSTRA // A*
#pragma region GET COST
auto getCost = [](int fromColumn, int fromRow, int toColumn, int toRow)
{
	return tileMap.GetTraversalCost(fromColumn, fromRow, toColumn, toRow);
};
#pragma endregion

// A*
#pragma region MANTHATTAN DISTANCE
auto manhattanDistance = [](int startX, int startY, int endX, int endY)
{
	return tileMap.ManhattanDistance(startX, startY, endX, endY);
};
#pragma endregion

#pragma region DIAGONAL DISTANCE
auto diagonalDistance = [](int startX, int startY, int endX, int endY)
{
	return tileMap.DiagonalDistance(startX, startY, endX, endY);
};
#pragma endregion

#pragma region EUCLIDEAN DISTANCE
auto euclideanDistance = [](int startX, int startY, int endX, int endY)
{
	return tileMap.EuclideanDistance(startX, startY, endX, endY);
};
#pragma endregion
#pragma endregion

#pragma region DRAW PATH
void DrawPath(bool pathFound)
{
	if (pathFound)
	{
		// Got a new path, clear the old one!
		path.clear();

		// Beginning from the end node, trace back to it's parent one at a time
		auto node = graph.GetNode(endX, endY);
		while (node != nullptr)
		{
			path.push_back(node);
			node = node->parent;
		}

		// Once we recorded all the position from end to start, we need to reverse
		// them to get the correct order
		std::reverse(path.begin(), path.end());
	}

	// It is also helpful to draw the closed list
	for (auto iter = closedList.begin(); iter != closedList.end(); ++iter)
	{
		auto node = (*iter);
		if (node->parent != nullptr)
		{
			auto from = GetPosition(node);
			auto to = GetPosition(node->parent);
			X::DrawScreenLine(from, to, X::Colors::Blue);
		}
	}

	// Draw the path
	for (size_t i = 0; i + 1 < path.size(); ++i)
	{
		auto from = GetPosition(path[i]);
		auto to = GetPosition(path[i + 1]);
		X::DrawScreenLine(from, to, X::Colors::Cyan);
	}

	// Draw sprites
	 mBatmanPosition = { static_cast<float>(startX) * 32, static_cast<float>(startY) * 32 };
	 mJokerPosition = { static_cast<float>(endX) * 32, static_cast<float>(endY) * 32 };
	 X::DrawSprite(mBatmanTextureId, mBatmanPosition, X::Pivot::TopLeft);
	 X::DrawSprite(mJokerTextureId, mJokerPosition, X::Pivot::TopLeft);
}
#pragma endregion

#pragma region SHOW PATHING UI
void ShowPathingUI()
{
	if (graph.GetColumns() != tileMap.GetColumns() ||
		graph.GetRows() != tileMap.GetRows())
	{
		graph.Initialize(tileMap.GetColumns(), tileMap.GetRows());
		startX = 0;
		startY = 0;
		endX = 0;
		endY = 0;
		path.clear();
		closedList.clear();
	}

	ImGui::Begin("Pathing", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	ImGui::SliderInt("Start X", &startX, 0, tileMap.GetColumns() - 1);
	ImGui::SliderInt("Start Y", &startY, 0, tileMap.GetRows() - 1);
	ImGui::SliderInt("End X", &endX, 0, tileMap.GetColumns() - 1);
	ImGui::SliderInt("End Y", &endY, 0, tileMap.GetRows() - 1);

	// Variables
	bool pathFound = false;

	BFS bfs;
	DFS dfs;
	Dijkstra dijkstra;
	AStar astar;

	if (ImGui::Button("Run BFS"))
	{
		if (bfs.Search(graph, startX, startY, endX, endY, isBlocked))
		{
			pathFound = true;
			closedList = bfs.GetClosedList();
		}
		else
		{
			path.clear();
		}
	}

	if (ImGui::Button("Run DFS"))
	{
		if (dfs.Search(graph, startX, startY, endX, endY, isBlocked))
		{
			pathFound = true;
			closedList = dfs.GetClosedList();

		}
		else 
		{
			path.clear();
		}
	}

	if (ImGui::Button("Run Dijkstra"))
	{
		if (dijkstra.Search(graph, startX, startY, endX, endY, isWalkable, getCost))
		{
			pathFound = true;
			closedList = dijkstra.GetClosedList();
		}
		else
		{
			path.clear();
		}
	}

	if (ImGui::Button("A* - Manhattan"))
	{
		if (astar.Search(graph, startX, startY, endX, endY, isWalkable, getCost, manhattanDistance))
		{
			pathFound = true;
			closedList = astar.GetClosedList();
		}
		else
		{
			path.clear();
		}
	}

	if (ImGui::Button("A* - Diagonal"))
	{
		if (astar.Search(graph, startX, startY, endX, endY, isWalkable, getCost, diagonalDistance))
		{
			pathFound = true;
			closedList = astar.GetClosedList();
		}
		else
		{
			path.clear();
		}
	}

	if (ImGui::Button("A* - Euclidean"))
	{
		if (astar.Search(graph, startX, startY, endX, endY, isWalkable, getCost, euclideanDistance))
		{
			pathFound = true;
			closedList = astar.GetClosedList();
		}
		else
		{
			path.clear();
		}
	}
	

	// Close the ImGui, else I will get an error
	ImGui::End();

	DrawPath(pathFound);
}
#pragma endregion

#pragma region GAME INIT
void GameInit()
{
	// tileMap.LoadMap("map_clean.txt");
	// tileMap.LoadMap("map_obstacles01.txt");
	// tileMap.LoadMap("map_obstacles02.txt");
	tileMap.LoadMap("map_blocked.txt");
	tileMap.LoadTiles("tileset.txt");

	mBatmanTextureId = X::LoadTexture("batman.png");
	mJokerTextureId = X::LoadTexture("joker.png");
}
#pragma endregion

#pragma region GAME LOOP
bool GameLoop(float deltaTime)
{
	tileMap.Update();
	tileMap.Render();
	tileMap.ShowDebugUI();

	ShowPathingUI();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}
#pragma endregion

#pragma region GAME CLEANUP
void GameCleanup()
{

}
#pragma endregion

#pragma region WIN MAIN
int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}
#pragma endregion