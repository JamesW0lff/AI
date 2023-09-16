#pragma once

#include <XEngine.h>

class Player
{
public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void SetPosition(const X::Math::Vector2& position) { mPosition = position; }
	const X::Math::Vector2& GetPosition() const { return mPosition; }

	X::Math::Circle GetBoundingCircle() const { return { mPosition, 30.0f }; }

	void ReceiveDamage();
	void Fire();

	void PlayerMovement(float deltaTime);

	void StopOutOfBounds(float deltaTime);

private:

	X::TextureId mTextureId = 0;

	float mSpriteWidth = 0.0f;
	float mSpriteHeight = 0.0f;

	X::Math::Vector2 mPosition = { 0.0f, 0.0f };

	int mHeatlh = 0;
	float mSpeed = 0.0f;
};