#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class WanderBehaviour : public SteeringBehaviour
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent) override;

		X::Math::Vector2 localWanderTarget;
		float wanderDistance = 100.0f;
		float wanderRadius = 10.0f;
		float wanderJitter = 1.0f;

	private:

		

	};
}