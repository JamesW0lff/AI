#pragma once

#include <XEngine.h>

class TileMap
{
public:
	~TileMap();

	void LoadMap(const char* fileName);

	void LoadTiles(const char* fileName);

	void Render() const;

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
		GRASS_2,		// grass_2.png			// 0
		FLOWER_2,		// flower_2.png			// 1
		TREE0_2,		// tree0_2.png			// 2
		TREE1_2,		// tree1_2.png			// 3
		TREE2_2,		// tree2_2.png			// 4
		TREE3_2			// tree3_2.png			// 5
	};
};