#pragma once

#include <XEngine.h>

class Player
{
public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void SetPosition(const X::Math::Vector2& position) { mPlayerPosition = position; }
	const X::Math::Vector2& GetPosition() const { return mPlayerPosition; }

	const X::Math::Vector2& GetLocation() const { return mPlayerLocation; }

	int GetPlayerHealth() { return mHealth; }
	
	void PlayerMovement(float deltaTime);
	void StopOutOfBounds();

	void FireGun();
	void ReceiveDamage(int damage);

	X::Math::Circle GetPlayerCollider() const { return { mPlayerPosition, 30.0f }; }

private:
	// ======= PLAYER =======
	X::TextureId mTextureId = 0;

	X::Math::Vector2 mPlayerPosition = X::Math::Vector2::Zero();
	X::Math::Vector2 mPlayerLocation = X::Math::Vector2::Zero();

	int mHealth = 0;
	float mSpeed = 0.0f;
	float mSpriteWidth = 0.0f;
	float mSpriteHeight = 0.0f;

	// ======= WEAPON =======
	X::TextureId mCrosshairTextureId = 0;

	X::SoundId mShootSountId = 0;

	// ======= SCREEN =======
	float screenWidth = 0.0f;
	float screenHeight = 0.0f;
	float rightBoundary = 0.0f;
	float leftBoundary = 0.0f;
	float topBoundary = 0.0f;
	float bottomBoundary = 0.0f;
	
};