#pragma once

#include <AI.h>
#include <XEngine.h>

class SeekBehaviour : public AI::SteeringBehaviour
{
public:
	X::Math::Vector2 Calculate(AI::Agent& nemesis) override
	{
		auto agentToDestination = nemesis.destination - nemesis.position;
		if (X::Math::MagnitudeSqr(agentToDestination) <= 0.0f)
			return X::Math::Vector2::Zero();

		auto direction = X::Math::Normalize(agentToDestination);
		return direction * nemesis.maxSpeed;
	}
};

class SCVEnemy : public AI::Agent
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void SetPosition(const X::Math::Vector2& pos) { position = pos; }
	const X::Math::Vector2& GetPosition() const { return position; }

	void SetEnemyActive(bool isActive) { mIsActive = isActive; }
	bool GetEnemyActive() { return mIsActive; }

	X::Math::Circle GetEnemyCollider() const { return { position, 30.0f }; }
	X::Math::Circle GetEnemyRange() const { return { position, 120.0f }; }

private:
	X::TextureId mEnemyTextureId;
	bool mIsActive = false;
	
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::WanderBehaviour* mWanderBehaviour = nullptr;
	SeekBehaviour* mDumbBehaviour = nullptr;
};