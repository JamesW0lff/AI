#include "Precompiled.h"
#include "WanderBehaviour.h"

#include "Agent.h"

using namespace AI;

X::Math::Vector2 WanderBehaviour::Calculate(Agent& agent)
{
	X::Math::Vector2 localTarget = localWanderTarget;
	X::Math::Vector2 randomAmount = { wanderJitter, wanderJitter };
	
	// Add small rnadom displacement to target
	X::Math::Vector2 newTarget = localTarget + X::RandomVector2(-randomAmount, randomAmount);

	// Project target back onto circle
	X::Math::Vector2 snappedTarget = X::Math::Normalize(newTarget) * wanderRadius;
	localWanderTarget = snappedTarget;

	// Project circle in front of agent
	X::Math::Vector2 projectedTarget = localWanderTarget + X::Math::Vector2{ 0.0f, wanderDistance };

	// Transform target into world space
	X::Math::Matrix3 worldTransform = agent.GetWorldTransform();
	X::Math::Vector2 worldWanderTarget = X::Math::TransformCoord(projectedTarget, worldTransform);

	X::Math::Vector2 circleCenter = X::Math::TransformCoord({ 0.0f, wanderDistance }, worldTransform);
	X::DrawScreenLine(agent.position, worldWanderTarget, X::Colors::Green);
	X::DrawScreenCircle(circleCenter, wanderRadius, X::Colors::Cyan);
	X::DrawScreenCircle(worldWanderTarget, 2.0f, X::Colors::Red);

	// Seek to wander target
	auto agentToTarget = worldWanderTarget - agent.position;
	auto desiredVelocity = X::Math::Normalize(agentToTarget) * agent.maxSpeed;
	return desiredVelocity - agent.velocity;
}