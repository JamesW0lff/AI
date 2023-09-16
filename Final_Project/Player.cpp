#include "Player.h"
#include "StalkingEnemy.h"
#include "SCVEnemy.h"

#include <string>

using std::string;

// ======= SINGLETON =======
extern StalkingEnemy stalkingEnemy;
extern SCVEnemy scvEnemy;

#pragma region NAMESPACE
namespace
{
	float startX = 1.0f;
	float startY = 1.0f;

	string health;

	X::Math::Vector2 GetCrosshairPostion()
	{
		const float mouseX = static_cast<float>(X::GetMouseScreenX());
		const float mouseY = static_cast<float>(X::GetMouseScreenY());

		return X::Math::Vector2(mouseX, mouseY);
	}

	X::Math::Vector2 pLocation = { 0.0f,0.0f };
}
#pragma endregion

#pragma region LOAD
void Player::Load()
{
	mTextureId = X::LoadTexture("jill_valentine_8bit.png");

	mSpriteWidth = X::GetSpriteWidth(mTextureId);
	mSpriteHeight = X::GetSpriteHeight(mTextureId);

	mCrosshairTextureId = X::LoadTexture("crosshair.png");
	mShootSountId = X::LoadSound("44magnum.wav");

	screenWidth = X::GetScreenWidth();
	screenHeight = X::GetScreenHeight();
	rightBoundary = screenWidth - (mSpriteWidth * 0.5);
	leftBoundary = 0.0f - mSpriteWidth * 0.5f;
	topBoundary = mSpriteHeight * 0.5f;
	bottomBoundary = screenHeight - (mSpriteHeight * 0.5f);

	mPlayerPosition = { startX * X::GetSpriteHeight(mTextureId), startY * X::GetSpriteHeight(mTextureId) };

	mHealth = 100;
	mSpeed = 250.0f;
}
#pragma endregion

#pragma region UNLOAD
void Player::Unload()
{
	mTextureId = 0;

	mSpriteWidth = 0.0f;
	mSpriteHeight = 0.0f;

	mCrosshairTextureId = 0;

	screenWidth = 0.0f;
	screenHeight = 0.0f;
	rightBoundary = 0.0f;
	leftBoundary = 0.0f;
	topBoundary = 0.0f;
	bottomBoundary = 0.0f;

	mPlayerPosition = X::Math::Vector2::Zero();
	mPlayerLocation = X::Math::Vector2::Zero();

	mHealth = 0;
	mSpeed = 0.0f;
}
#pragma endregion

#pragma region UPDATE
void Player::Update(float deltaTime)
{
	// ======= PLAYER MOVEMENT =======
	PlayerMovement(deltaTime);

	// ======= STOP OUT OF BOUNDS =======
	StopOutOfBounds();

	// ======= FIRE GUN =======
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		FireGun();
	}

	// ======= SET PLAYER'S LAST LOCATION =======
	if (mPlayerLocation.x != 0.0f && mPlayerLocation.y != 0.0f)
	{
		X::DrawScreenDiamond(mPlayerLocation, 20.0f, X::Colors::DarkBlue);
	}
}
#pragma endregion

#pragma region RENDER
void Player::Render()
{
	// ======= PLAYER =======
	X::DrawSprite(mTextureId, mPlayerPosition, X::Pivot::Center);
	X::DrawSprite(mCrosshairTextureId, GetCrosshairPostion());
	X::DrawScreenCircle(GetPlayerCollider(), X::Colors::Cyan);

	// ======= DISPLAY PLAYER HEALTH =======
	health = std::to_string(GetPlayerHealth());
	X::DrawScreenText("Heatlh: ", 900.0f, 40.0f, 30.0f, X::Colors::Black);
	X::DrawScreenText(health.c_str(), 1100.0f, 40.0f, 30.0f, X::Colors::Black);

}
#pragma endregion

#pragma region PLAYER MOVEMENT
void Player::PlayerMovement(float deltaTime)
{
	// ======= MOVEMENT: RIGHT =======
	if (X::IsKeyDown(X::Keys::D) || X::IsKeyDown(X::Keys::RIGHT))
	{
		mPlayerPosition.x += mSpeed * deltaTime;
	}
	// ======= MOVEMENT: LEFT =======
	else if (X::IsKeyDown(X::Keys::A) || X::IsKeyDown(X::Keys::LEFT))
	{
		mPlayerPosition.x -= mSpeed * deltaTime;
	}
	// ======= MOVEMENT: UP =======
	else if (X::IsKeyDown(X::Keys::W) || X::IsKeyDown(X::Keys::UP))
	{
		mPlayerPosition.y -= mSpeed * deltaTime;
	}
	// ======= MOVEMENT: DOWN =======
	else if (X::IsKeyDown(X::Keys::S) || X::IsKeyDown(X::Keys::DOWN))
	{
		mPlayerPosition.y += mSpeed * deltaTime;
	}
}
#pragma endregion

#pragma region STOP OUT OF BOUNDS
void Player::StopOutOfBounds()
{
	// ======= RIGHT BOUNDARY =======

	if (mPlayerPosition.x > rightBoundary)
	{
		mPlayerPosition.x = rightBoundary;
	}
	// ======= LEFT BOUNDARY =======

	if (mPlayerPosition.x < leftBoundary)
	{
		mPlayerPosition.x = leftBoundary;
	}

	// ======= TOP BOUNDARY =======
	if (mPlayerPosition.y < topBoundary)
	{
		mPlayerPosition.y = topBoundary;
	}
	// ======= BOTTOM BOUNDARY =======
	if (mPlayerPosition.y > bottomBoundary)
	{
		mPlayerPosition.y = bottomBoundary;
	}
}
#pragma endregion

#pragma region FIRE GUN
void Player::FireGun()
{
	mPlayerLocation = GetPosition();
	X::DrawScreenDiamond(mPlayerLocation, 20.0f, X::Colors::DarkBlue);

	X::PlaySoundOneShot(mShootSountId);

	if (!stalkingEnemy.GetEnemyActive())
	{
		stalkingEnemy.SetEnemyActive(true);
		scvEnemy.SetEnemyActive(false);
		X::Math::Vector2 nemesisPos = scvEnemy.GetPosition();
		stalkingEnemy.SetPosition(nemesisPos);
	}

	stalkingEnemy.ChangeState(EnemyState::LocatePlayer);
	
}
#pragma endregion

#pragma region RECEIVE DAMAGE
void Player::ReceiveDamage(int damage)
{
	mHealth -= damage;
}
#pragma endregion