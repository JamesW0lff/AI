
#include "Player.h"

#pragma region NAMESPACE
namespace
{
	float START_X = 0.0f;
	float START_Y = 0.0f;
}
#pragma endregion

#pragma region LOAD
void Player::Load()
{
	mTextureId = X::LoadTexture("leon_s_kennedy_8bit.png");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mSpriteHeight = X::GetSpriteHeight(mTextureId);

	mPosition = { START_X * X::GetSpriteHeight(mTextureId) , START_Y * X::GetSpriteHeight(mTextureId) };

	mHeatlh = 100;
	mSpeed = 250.0f;
}
#pragma endregion

#pragma region UNLOAD
void Player::Unload()
{
	mTextureId = 0;

	mSpriteWidth = 0.0f;
	mSpriteHeight = 0.0f;

	mPosition = { 0.0f, 0.0f };

	mHeatlh = 0;
	mSpeed = 0.0f;
}
#pragma endregion

#pragma region UPDATE
void Player::Update(float deltaTime)
{
	// ======= PLAYER MOVEMENT =======
	PlayerMovement(deltaTime);

	// ======= OUT OF BOUNDS =======
	StopOutOfBounds(deltaTime);
}
#pragma endregion

#pragma region RENDER
void Player::Render()
{
	X::DrawSprite(mTextureId, mPosition, X::Pivot::TopLeft);
}
#pragma endregion

#pragma region RECEIVE DAMAGE
void Player::ReceiveDamage()
{

}
#pragma endregion

#pragma region FIRE
void Player::Fire()
{

}
#pragma endregion

#pragma region PLAYER MOVEMENT
void Player::PlayerMovement(float deltaTime)
{
	// ======= MOVEMENT: RIGHT =======
	if (X::IsKeyDown(X::Keys::D) || X::IsKeyDown(X::Keys::RIGHT))
	{
		mPosition.x += mSpeed * deltaTime;
	}
	// ======= MOVEMENT: LEFT =======
	else if (X::IsKeyDown(X::Keys::A) || X::IsKeyDown(X::Keys::LEFT))
	{
		mPosition.x -= mSpeed * deltaTime;
	}
	// ======= MOVEMENT: UP =======
	else if (X::IsKeyDown(X::Keys::W) || X::IsKeyDown(X::Keys::UP))
	{
		mPosition.y -= mSpeed * deltaTime;
	}
	// ======= MOVEMENT: DOWN =======
	else if (X::IsKeyDown(X::Keys::S) || X::IsKeyDown(X::Keys::DOWN))
	{
		mPosition.y += mSpeed * deltaTime;
	}
}
#pragma endregion

#pragma region STOP OUT OF BOUNDS
void Player::StopOutOfBounds(float deltaTime)
{
	float screenWidth = X::GetScreenWidth();
	float screenHeight = X::GetScreenHeight();

	// ======= RIGHT BOUNDARY =======
	if (mPosition.x > screenWidth - (mSpriteWidth * 0.5))
	{
		mPosition.x = screenWidth - (mSpriteWidth * 0.5);
	}
	// ======= LEFT BOUNDARY =======
	if (mPosition.x < mSpriteWidth)
	{
		mPosition.x = mSpriteWidth;
	}
	// ======= TOP BOUNDARY =======
	if (mPosition.y < (mSpriteHeight * 0.5f))
	{
		mPosition.y = mSpriteHeight * 0.5f;
	}
	// ======= BOTTOM BOUNDARY =======
	if (mPosition.y > screenHeight - (mSpriteHeight * 0.5f))
	{
		mPosition.y = screenHeight - mSpriteHeight * 0.5f;
	}
}
#pragma endregion