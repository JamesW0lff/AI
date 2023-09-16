#pragma once

#include "SteeringBehaviour.h"

namespace AI
{
	class SteeringModule
	{
	public:
		SteeringModule(Agent& agent);

		template <class NewBehaviourType>
		NewBehaviourType* AddBehaviour()
		{
			auto& newBehaviour = mBehaviours.emplace_back(std::make_unique<NewBehaviourType>());
			return static_cast<NewBehaviourType*>(newBehaviour.get());
		}

		void Purge();

		X::Math::Vector2 Calculate() const;

	private:
		Agent& mAgent;
		std::vector<std::unique_ptr<SteeringBehaviour>> mBehaviours;
	};
}