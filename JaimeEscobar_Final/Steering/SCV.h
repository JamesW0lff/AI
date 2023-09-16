#pragma once

#include <AI.h>
#include <XEngine.h>

class SeekBehaviour : public AI::SteeringBehaviour
{
public:
	X::Math::Vector2 Calculate(AI::Agent& agent) override
	{
		auto agentToDestination = agent.destination - agent.position;
		if (X::Math::MagnitudeSqr(agentToDestination) <= 0.0f)
			return X::Math::Vector2::Zero();

		auto direction = X::Math::Normalize(agentToDestination);
		return direction * agent.maxSpeed;
	}
};

class SCV : public AI::Agent
{
public:
	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

private:
	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::WanderBehaviour* mWanderBehaviour = nullptr;
	SeekBehaviour* mDumbBehaviour = nullptr;
	X::TextureId mTextureIds[16];
};