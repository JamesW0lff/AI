#pragma once

#include <XEngine.h>

namespace AI
{
	// Essentially BaseGameEntity and MovingEntity from slides
	struct Agent
	{
		X::Math::Matrix3 GetWorldTransform() const
		{
			// For
			X::Math::Vector2 f = heading;
			// Side
			X::Math::Vector2 s = X::Math::PerpendicularRH(f);
			X::Math::Vector2 d = position;
			return
			{
				s.x, s.y, 0.0f,
				f.x, f.y, 0.0f,
				d.x, d.y, 1.0f
			};
		}

		X::Math::Vector2 position = X::Math::Vector2::Zero();
		X::Math::Vector2 velocity = X::Math::Vector2::Zero();
		X::Math::Vector2 destination = X::Math::Vector2::Zero();
		X::Math::Vector2 heading = X::Math::Vector2::YAxis();
		float radius = 1.0f;
		float mass = 1.0f;
		float maxSpeed = 100.0f;
	};
}