#pragma once

#include <AI.h>
#include <XEngine.h>

enum class EnemyState 
{
	Idle,
	SeekPlayer,
	LocatePlayer,
	ChasePlayer,
	AttackPlayer
};

class StalkingEnemy
{
public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void NearbyPlayer();

	void ChangeState(EnemyState nextState);

	void SetPosition(const X::Math::Vector2& pos) { mEnemyPosition = pos; }
	const X::Math::Vector2& GetPosition() const { return mEnemyPosition; }

	void SetTarget(X::Math::Vector2 target) { mTarget = target; }
	X::Math::Vector2 GetTarget() { return mTarget; }

	X::Math::Circle GetEnemyCollider() const { return { mEnemyPosition, 30.0f }; }
	X::Math::Circle GetEnemyRange() const {	return { mEnemyPosition, 120.0f }; }

	X::TextureId GetTextureId() { return mEnemyTextureId; }

	void SetEnemyActive(bool isActive) { mIsActive = isActive; }
	bool GetEnemyActive() { return mIsActive; }

private:

	// ======= STALKING ENEMY =======
	std::unique_ptr<AI::StateMachine<StalkingEnemy>> mStateMachine;

	X::TextureId mEnemyTextureId = 0;
	X::SoundId mEnemySoundId = 0;
	
	X::Math::Vector2 mEnemyPosition = X::Math::Vector2::Zero();
	X::Math::Vector2 mTarget = X::Math::Vector2::Zero();

	bool mIsActive = false;

	// ======= SCREEN =======
	float screenWidth = 0.0f;
	float screenHeight = 0.0f;

	float mCollisionTimer = 0.0f;

};