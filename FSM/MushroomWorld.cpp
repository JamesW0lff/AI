#include "MushroomWorld.h"

#pragma region NAMESPACE
namespace
{
	constexpr size_t mushroomCount = 10;
}
#pragma endregion

#pragma region SINGLETON
MushroomWorld& MushroomWorld::Get()
{
	static MushroomWorld instance;
	return instance;
}
#pragma endregion

#pragma region LOAD
void MushroomWorld::Load()
{
	mMushroomCollected.resize(mushroomCount, false);
	for (size_t i = 0; i < mushroomCount; ++i)
	{
		mMushroomPositions.push_back(X::RandomVector2({ 100.0f, 100.0f }, { 1000.0f, 620.f }));
	}

	mTextureId = X::LoadTexture("mushroom.png");
}
#pragma endregion

#pragma region UNLOAD
void MushroomWorld::Unload()
{
	mTextureId = 0;
}
#pragma endregion

#pragma region RENDER
void MushroomWorld::Render()
{
	for (size_t i = 0; i < mMushroomPositions.size(); ++i)
	{
		if (!mMushroomCollected[i])
		{
			X::DrawSprite(mTextureId, mMushroomPositions[i]);
		}
	}
}
#pragma endregion

#pragma region COLLECT MUSHROOM
void MushroomWorld::CollectMushroom(size_t index)
{
	mMushroomCollected[index] = true;
}
#pragma endregion

#pragma region GET MUSHROOM POSITION
const X::Math::Vector2& MushroomWorld::GetMushroomPosition(size_t index) const
{
	return mMushroomPositions[index];
}
#pragma endregion

#pragma region IS MUSHROOM COLLECTED
bool MushroomWorld::IsMushroomCollected(size_t index) const
{
	return mMushroomCollected[index];
}
#pragma endregion

#pragma region GET MUSHROOMS LEFT
size_t MushroomWorld::GetMushroomsLeft() const
{
	size_t left = 0;
	for (auto collected : mMushroomCollected)
	{
		if (!collected)
		{
			left++;
		}
	}
	
	return left;
}
#pragma endregion