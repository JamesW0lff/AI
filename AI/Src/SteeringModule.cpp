#include "Precompiled.h"
#include "SteeringModule.h"

using namespace AI;

SteeringModule::SteeringModule(Agent& agent)
	: mAgent(agent)
{}

void SteeringModule::Purge()
{
	mBehaviours.clear();
}

X::Math::Vector2 SteeringModule::Calculate() const
{
	X::Math::Vector2 totalForce;
	for (auto& behaviour : mBehaviours)
	{
		if (behaviour->IsActive())
		{
			totalForce += behaviour->Calculate(mAgent) * behaviour->GetWeight();
		}
	}
	return totalForce;
}
