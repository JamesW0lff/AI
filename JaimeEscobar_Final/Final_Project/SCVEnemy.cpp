#include "Player.h"
#include "StalkingEnemy.h"
#include "SCVEnemy.h"

// ======= SINGLETON =======
extern StalkingEnemy stalkingEnemy;
extern Player player;
extern float gWanderDistance;
extern float gWanderRadius;
extern float gWanderJitter;

#pragma region LOAD
void SCVEnemy::Load()
{
	// Set agent attributes
	radius = 16.0f;
	mass = 1.0f;
	maxSpeed = 200.0f;

	mSteeringModule = std::make_unique<AI::SteeringModule>(*this);

	mWanderBehaviour = mSteeringModule->AddBehaviour<AI::WanderBehaviour>();

	mWanderBehaviour->SetActive(true);

	// Enemy Settings
	mEnemyTextureId = stalkingEnemy.GetTextureId();
	position = stalkingEnemy.GetPosition();

}
#pragma endregion

#pragma region UNLOAD
void SCVEnemy::Unload()
{
	mSteeringModule.reset();
}
#pragma endregion

#pragma region UPDATE
void SCVEnemy::Update(float deltaTime)
{
	if (mIsActive)
	{
		// Apply tuning
		mWanderBehaviour->wanderDistance = gWanderDistance;
		mWanderBehaviour->wanderRadius = gWanderRadius;
		mWanderBehaviour->wanderJitter = gWanderJitter;

		auto force = mSteeringModule->Calculate();
		auto acceleration = force / mass;
		velocity += acceleration * deltaTime;
		position += velocity * deltaTime;

		// Adjust heading if we are moving
		if (X::Math::MagnitudeSqr(velocity) > 1.0f)
			heading = X::Math::Normalize(velocity);

		const float screenWidth = static_cast<float>(X::GetScreenWidth());
		const float screenHeight = static_cast<float>(X::GetScreenHeight());
		if (position.x < 0.0f)
			position.x += screenWidth;
		if (position.x > screenWidth)
			position.x -= screenWidth;
		if (position.y < 0.0f)
			position.y += screenHeight;
		if (position.y > screenHeight)
			position.y -= screenHeight;

		// Check if the player is nearby
		if (X::Math::Intersect(player.GetPlayerCollider(), GetEnemyRange()))
		{
			stalkingEnemy.SetEnemyActive(true);
			SetEnemyActive(false);
			X::Math::Vector2 nemesisPos = GetPosition();
			stalkingEnemy.SetPosition(nemesisPos);
			stalkingEnemy.ChangeState(EnemyState::ChasePlayer);
		}
	}
}
#pragma endregion

#pragma region RENDER
void SCVEnemy::Render()
{
	if (mIsActive)
	{
		X::DrawSprite(mEnemyTextureId, position, X::Pivot::Center);
		X::DrawScreenCircle({ position , 30.0f}, X::Colors::DarkCyan);
		X::DrawScreenCircle({ position , 120.0f}, X::Colors::DarkGreen);
	}
}
#pragma endregion