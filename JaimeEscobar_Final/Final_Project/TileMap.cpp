#include "TileMap.h"

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
	FILE* mapFile = nullptr;

	fopen_s(&mapFile, fileName, "r");

	fscanf_s(mapFile, "Columns: %d\n", &mColumns);
	fscanf_s(mapFile, "Rows: %d\n", &mRows);

	delete[] mMap;

	XASSERT(mapFile != nullptr, "Error opening the file. Please check the name/ path is correct");

	mMap = new int[mColumns * mRows];

	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			const int tileIndex = fgetc(mapFile) - '0';
			mMap[GetIndex(c, r, mColumns)] = tileIndex;
		}
		fgetc(mapFile);
	}

	fclose(mapFile);
}
#pragma endregion

#pragma region LOAD TILES
void TileMap::LoadTiles(const char* fileName)
{
	FILE* tileFile = nullptr;

	fopen_s(&tileFile, fileName, "r");

	int tileCount = 0;

	fscanf_s(tileFile, "TileCount: %d\n", &tileCount);

	mTileSet.clear();

	mTileSet.resize(tileCount);

	for (int i = 0; i < tileCount; ++i)
	{
		char buffer[256];
		fscanf_s(tileFile, "%s\n", buffer, static_cast<uint32_t>(std::size(buffer)));
		mTileSet[i] = X::LoadTexture(buffer);
	}

	fclose(tileFile);

	mTileWidth = X::GetSpriteWidth(mTileSet.front());
	mTileHeight = X::GetSpriteHeight(mTileSet.front());
}
#pragma endregion

#pragma region RENDER
void TileMap::Render() const
{
	for (int r = 0; r < mRows; ++r)
	{
		for (int c = 0; c < mColumns; ++c)
		{
			const int tileIndex = mMap[GetIndex(c, r, mColumns)];
			const X::TextureId textureId = mTileSet[tileIndex];
			const X::Math::Vector2 position = { static_cast<float>(c * mTileWidth), static_cast<float>(r * mTileHeight) };
			X::DrawSprite(textureId, position, X::Pivot::TopLeft);
		}
	}
}
#pragma endregion

#pragma region GET INDEX
int TileMap::GetIndex(int column, int row, int columnCount) const
{
	return column + (row * columnCount);
}
#pragma endregion