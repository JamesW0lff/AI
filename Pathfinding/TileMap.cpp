#include "TileMap.h"
#include <ImGui/Inc/imgui.h>

using std::string;
using std::min;

#pragma region NAMESPACE
namespace
{
	int ToIndex(int column, int row, int totalColumns)
	{
		return column + (row * totalColumns);
	}

	X::Math::Vector2 GetTargetPosition()
	{
		const int mouseX = X::GetMouseScreenX();
		const int mouseY = X::GetMouseScreenY();

		return X::Math::Vector2(static_cast<float>(mouseX), static_cast<float>(mouseY));
	}

	

}
#pragma endregion

#pragma region ~TILE MAP
TileMap::~TileMap()
{
	delete[] mMap;
	mMap = nullptr;
}
#pragma endregion

#pragma region LOAD MAP
void TileMap::LoadMap(const char* fileName)
{
	// TODO:
	// Use fopen_s to open a txt file with the following contents:
	//
	// Columns: 30
	// Rows: 20
	// 000000000000000000000000000000
	// 000000000000000000000000000000
	// 000000000000000000000000000000
	// ....
	//
	// Once you have a FILE pointer, use fscanf_s to read in the
	// rows and columns. Watch out for new line characters, you will need
	// to consume those as well so you are at the correct location when
	// reading the file.
	//
	// e.g.    fscanf_s(file, "Columns: %d\n", &mColumns);
	// fopen_s(&reference, "<file_name>", "<mode>"); <mode> = "r" -> read || "w" -> write || "a" -> append || "r+" -> read & write 
	// errno_t err;
	FILE* mapFile = nullptr;

	//err = fopen_s(&mapFile, fileName, "r");
	fopen_s(&mapFile, fileName, "r");

	// XASSERT(err == 0, "Error openning the file. Please check the name/ path is correct.");

	// mColumns = 15;
	// mRows = 10;

	fscanf_s(mapFile, "Columns: %d\n", &mColumns);
	fscanf_s(mapFile, "Rows: %d\n", &mRows);

	// Make sure to free any existing memory you are currently using
	// before allocating a new array of size columns * rows.
	delete[] mMap;

	XASSERT(mapFile != nullptr, "Error opening the file. Please check the name/ path is correct");

	mMap = new int[mColumns * mRows];

	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			// TODO: Once you are in this part of the file, you need
			// to read one character at a time using fgetc. Once you have
			// the character, you want to turn it into a number for the
			// tileset array.
			//
			// e.g. tileIndex = fgetc(...) - '0'; // subtract value 48
			const int tileIndex = fgetc(mapFile) - '0'; // TEMP until we use fgetc
			// index = GetIndex(c, r, mColumns);
			// mMap[index]
			mMap[GetIndex(c, r, mColumns)] = tileIndex;
		}
		// TODO:
		// Use one extra call to fgetc() here so we jump to the next line
		// in our txt file.
		// fgetc(file)
		fgetc(mapFile);
	}

	fclose(mapFile);
}
#pragma endregion

#pragma region SAVE MAP
void TileMap::SaveMap(const char* fileName)
{
	// TODO:
	// This is basically the opposite of LoadMap, but use fprintf_s instead.
	FILE* mapFile = nullptr;

	fopen_s(&mapFile, fileName, "w");

	// XASSERT(err == 0, "Error openning the file. Please check the name/ path is correct.");

	fprintf_s(mapFile, "Columns: %d\n", mColumns);
	fprintf_s(mapFile, "Rows: %d\n", mRows);

	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			const int tile = mMap[GetIndex(c, r, mColumns)];
			fprintf_s(mapFile, "%d");
		}
		fprintf_s(mapFile, "\n");
	}

	fclose(mapFile);
}
#pragma endregion

#pragma region LOAD TILES
void TileMap::LoadTiles(const char* fileName)
{
	// TODO:
	// Update the code to load from file
	// errno_t err;
	FILE* tileFile = nullptr;

	// err = fopen_s(&tileFile, fileName, "r");
	fopen_s(&tileFile, fileName, "r");

	// XASSERT(err == 0, "Error openning the file. Please check the name/ path is correct.");

	int tileCount = 0;

	fscanf_s(tileFile, "TileCount: %d\n", &tileCount);
	
	// Clear the old set
	mTileSet.clear();

	// XASSERT(tileFile != nullptr, "Error openning the file. Please check the name/ path is correct.");

	mTileSet.resize(tileCount);

	// TEMP: Hardcoding these for now
	// mTileSet.push_back(X::LoadTexture("grass.png"));
	// mTileSet.push_back(X::LoadTexture("flower.png"));
	// mTileSet.push_back(X::LoadTexture("stone.png"));
	// mTileSet.push_back(X::LoadTexture("tree0.png"));
	// mTileSet.push_back(X::LoadTexture("tree1.png"));
	// mTileSet.push_back(X::LoadTexture("tree2.png"));
	// mTileSet.push_back(X::LoadTexture("tree3.png"));

	for (int i = 0; i < tileCount; ++i)
	{
		// string buffer;
		char buffer[256];
		fscanf_s(tileFile, "%s\n", buffer, static_cast<uint32_t>(std::size(buffer)));
		mTileSet[i] = X::LoadTexture(buffer);
		// fscanf_s(tileFile, "\n");
	}

	fclose(tileFile);

	// Assume all the tiles are the same size
	mTileWidth = X::GetSpriteWidth(mTileSet.front());
	mTileHeight = X::GetSpriteHeight(mTileSet.front());
}
#pragma endregion

#pragma region RESIZE
void TileMap::Resize(int columns, int rows)
{
	// If the dimension is the same, nothing to do!
	if (columns == mColumns && rows == mRows)
		return;

	// If the inputs are invalid, cannot proceed.
	if (columns <= 0 || rows <= 0)
		return;

	// Allocate a new map with the given dimensions
	int* newMap = new int[columns * rows];

	// TODO:
	// Use a nested for loop to copy existing data to the new map
	// *Warning* you need to be aware of the dimensions of both arrays!

	// TEMP:
	// This clears the map to 0
	for (int r = 0; r < rows; ++r)
	{
		for (int c = 0; c < columns; ++c)
		{
			const int index = GetIndex(c, r, columns);
			newMap[index] = 0;
		}
	}

	for (int r = 0; r < X::Math::Min(rows, mRows); ++r)
	{
		for (int c = 0; c < X::Math::Min(columns, mColumns); ++c)
		{
			const int index = GetIndex(c, r, columns);
			const int index02 = GetIndex(c, r, mColumns);
			newMap[index] = mMap[index02];
		}
	}

	mColumns = columns;
	mRows = rows;
	delete[] mMap;
	mMap = newMap;
}
#pragma endregion

#pragma region UPDATE
void TileMap::Update()
{
	if (X::IsMouseDown(X::Mouse::LBUTTON))
	{
		const int mouseX = X::GetMouseScreenX();
		const int mouseY = X::GetMouseScreenY();
		const int column = mouseX / mTileWidth;
		const int row = mouseY / mTileHeight;

		const int index = GetIndex(column, row, mColumns);
		mMap[index] = mSelectedTile;
	}
}
#pragma endregion

#pragma region RENDER
void TileMap::Render() const
{
	// TODO:
	// Finish this part using double for-loop
	for (int r = 0; r < mRows; ++r)
	{
		for(int c = 0; c < mColumns; ++c)
		{
			const int tileIndex = mMap[GetIndex(c, r, mColumns)];
			const X::TextureId textureId = mTileSet[tileIndex];
			const X::Math::Vector2 position = { static_cast<float>(c * mTileWidth), static_cast<float>(r * mTileHeight) };
			X::DrawSprite(textureId, position, X::Pivot::TopLeft);
		}
	}
}
#pragma endregion

#pragma region SHOW DEBUG UI
void TileMap::ShowDebugUI()
{
	ImGui::Begin("Map Editor", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

	if (ImGui::Button("Load Map"))
	{
		char fileName[MAX_PATH] = {};
		if (X::OpenFileDialog(fileName, "Load Map", "Map Files (*.txt)\0*.txt"))
			LoadMap(fileName);
	}
	if (ImGui::Button("Save Map"))
	{
		char fileName[MAX_PATH] = {};
		if (X::SaveFileDialog(fileName, "Save Map", "Map Files (*.txt)\0*.txt"))
			SaveMap(fileName);
	}

	static int columns = mColumns;
	static int rows = mRows;
	ImGui::SliderInt("Columns", &columns, 5, 50);
	ImGui::SliderInt("Rows", &rows, 5, 50);
	if (ImGui::Button("Resize Map"))
		Resize(columns, rows);

	for (int i = 0; i < (int)mTileSet.size(); ++i)
	{
		if (ImGui::ImageButton(X::GetSprite(mTileSet[i]), { (float)mTileWidth, (float)mTileHeight }))
			mSelectedTile = i;
		if (i + 1 < (int)mTileSet.size())
			ImGui::SameLine();
	}

	ImGui::End();
}
#pragma endregion

#pragma region IS BLOCKED
bool TileMap::IsBlocked(int column, int row) const
{
	// Check the position is not equal to an object that 'blocks' the path
	const int tile = mMap[ToIndex(column, row, mColumns)];
	if (column < 0 || column >= mColumns ||
		row < 0 || row >= mRows ||
		tile == FLOWER		||
		tile == STONE		|| 
		tile == TREE0		||
		tile == TREE1		||
		tile == TREE2		||
		tile == TREE3		||
		tile == WATER		||
		tile == WATER_WAVES ||
		tile == FLOWER_2	||
		tile == TREE0_2		||
		tile == TREE1_2		||
		tile == TREE2_2		||
		tile == TREE3_2)
		return true;

	return false;
}
#pragma endregion

#pragma region IS WALKABLE
bool TileMap::IsWalkable(int toColumn, int toRow) const
{
	// Check the position is not equal to an object that 'blocks' the path
	const int tile = mMap[ToIndex(toColumn, toRow, mColumns)];
	if (toColumn < 0 || toColumn >= mColumns ||
		toRow < 0 || toRow >= mRows ||
		tile == STONE ||
		tile == TREE0 ||
		tile == TREE1 ||
		tile == TREE2 ||
		tile == TREE3 ||
		tile == TREE0_2 ||
		tile == TREE1_2 ||
		tile == TREE2_2 ||
		tile == TREE3_2)
		return false;

	return true;
}
#pragma endregion

#pragma region MANHATTAN DISTANMCE
float TileMap::ManhattanDistance(int startX, int startY, int endX, int endY) const
{
	// abs = absolute value of an integer number
	float dx = abs(startX - endX);
	float dy = abs(startY - endY);

	return dx + dy;
}
#pragma endregion

#pragma region DIAGONAL DISTANMCE
float TileMap::DiagonalDistance(int startX, int startY, int endX, int endY) const
{
	float dx = abs(startX - endX);
	float dy = abs(startY - endY);

	//D2 = sqrt(2)
	// octile distance
	float D2 = sqrt(2);

	return (dx + dy) + (D2 - 2) * min(dx, dy);
}
#pragma endregion

#pragma region EUCLIDEAN DISTANCE
float TileMap::EuclideanDistance(int startX, int startY, int endX, int endY) const
{
	// dx = abs(node.x - goal.x)
	// dy = abs(node.y - goal.y)
	
	// return sqrt(dx * dx + dy * dy);

	// In XEngine: 
	// Distance(const Vector2& a, const Vector2& b) { return Sqrt(DistanceSqr(a, b)); }
	// float DistanceSqr(const Vector2& a, const Vector2& b) { return MagnitudeSqr(a - b); }
	// float MagnitudeSqr(const Vector2& v) { return (v.x * v.x) + (v.y * v.y); }
	return X::Math::Distance(X::Math::Vector2(startX, startY), X::Math::Vector2(endX, endY));
}
#pragma endregion

#pragma region GET TRAVERSAL COST
float TileMap::GetTraversalCost(int fromColumn, int fromRow, int toColumn, int toRow) const
{
	int index = mMap[ToIndex(toColumn, toRow, mColumns)];
	bool isDiagonal = (fromColumn != toColumn) && (fromRow != toRow);

	float cost = 0;

	// assign a cost to each tile
	switch (index)
	{
		case GRASS:
			cost = 1;
			break;

		case GRASS_2:
			cost = 1.5;
			break;

		case FLOWER:
			cost = 2;
			break;

		case FLOWER_2:
			cost = 2.5;
			break;

		case STONE:
			cost = 3;
			break;

		case TREE0:
		case TREE1:
		case TREE2:
		case TREE3:
			cost = 4;
			break;

		case TREE0_2:
		case TREE1_2:
		case TREE2_2:
		case TREE3_2:
			cost = 4.5;
			break;

		case WATER:
		case WATER_WAVES:
			cost = 5;
			break;
	}

	return cost * (isDiagonal ? 1.414f : 1.0f);

}
#pragma endregion

#pragma region GET INDEX
int TileMap::GetIndex(int column, int row, int columnCount) const
{
	return column + (row * columnCount);
}
#pragma endregion