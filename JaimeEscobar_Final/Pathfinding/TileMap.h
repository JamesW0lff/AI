#pragma once

#include <XEngine.h>

// Description:
// Store tile types used at each location (i.e. column, row) as an 1D array of integers.
// The index of each slot can be obtained using the GetIndex(...) helper function.
class TileMap
{
public:
	~TileMap();

	void LoadMap(const char* fileName);
	void SaveMap(const char* fileName);

	void LoadTiles(const char* fileName);

	void Resize(int columns, int rows);

	void Update();
	void Render() const;
	void ShowDebugUI();

	bool IsBlocked(int column, int row) const;
	bool IsWalkable(int column, int row) const;

	float ManhattanDistance(int startX, int startY, int endX, int endY) const;
	float DiagonalDistance(int startX, int startY, int endX, int endY) const;
	float EuclideanDistance(int startX, int startY, int endX, int endY) const;

	float GetTraversalCost(int fromColumn, int fromRow, int toColumn, int toRow) const;

	float GetEstimatedDistance(int startColumn, int startRow, int endColumn, int endRow) const;

	int GetColumns() const { return mColumns; }
	int GetRows() const { return mRows; }
	int GetTileWidth() const { return mTileWidth; }
	int GetTileHeight() const { return mTileHeight; }

private:
	int GetIndex(int column, int row, int columnCount) const;

	int* mMap = nullptr;	// Default member initialization
	int mColumns = 0;
	int mRows = 0;

	std::vector<X::TextureId> mTileSet; // Actual textures to use for each location
	int mTileWidth = 0;
	int mTileHeight = 0;
	int mSelectedTile = 0;

	enum TileFiles
	{
		GRASS,			// grass.png			// 0
		FLOWER,			// flower.png			// 1
		STONE,			// stone.png			// 2
		TREE0,			// tree0.png			// 3
		TREE1,			// tree1.png			// 4
		TREE2,			// tree2.png			// 5
		TREE3,			// tree3.png			// 6
		WATER,			// water.png			// 7
		WATER_WAVES,	// water_waves.png		// 8
		GRASS_2,		// grass_2.png			// 9
		FLOWER_2,		// flower_2.png			// 10
		TREE0_2,		// tree0_2.png			// 11
		TREE1_2,		// tree1_2.png			// 12
		TREE2_2,		// tree2_2.png			// 13
		TREE3_2			// tree3_2.png			// 14
	};
};