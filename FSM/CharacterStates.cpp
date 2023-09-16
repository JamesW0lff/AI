#include "CharacterStates.h"
#include "MushroomWorld.h"

void MoveToMushroomState::Enter(Character& mario)
{

}

void MoveToMushroomState::Update(Character& mario, float deltaTime)
{
	size_t target = mario.GetTargetMushroom();
	auto targetPos = MushroomWorld::Get().GetMushroomPosition(target);
	if (X::Math::Distance(mario.GetPosition(), targetPos) < 10.0f)
	{
		size_t nextTarget = target + 1;
		if (nextTarget >= MushroomWorld::Get().GetMushroomsLeft())
		{
			nextTarget = 0;
		}
		mario.SetTargetMushroom(nextTarget);
	}
	else
	{
		auto direction = X::Math::Normalize(targetPos - mario.GetPosition());
		auto velocity = direction * 300.0f;
		mario.SetPosition(mario.GetPosition() + (velocity * deltaTime));
	}
}

void MoveToMushroomState::Exit(Character& mario)
{

}

void EatMushroomState::Enter(Character& mario)
{

}

void EatMushroomState::Update(Character& mario, float deltaTime)
{

}

void EatMushroomState::Exit(Character& mario)
{

}