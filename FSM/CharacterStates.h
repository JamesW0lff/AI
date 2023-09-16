#pragma once

#include <AI.h>
#include <XEngine.h>

#include "Character.h"

class MoveToMushroomState : public AI::State<Character>
{
public:

	void Enter(Character& mario) override;
	void Update(Character& mario, float deltaTime) override;
	void Exit(Character& mario) override;

};

class EatMushroomState : public AI::State<Character>
{
public:

	void Enter(Character& mario) override;
	void Update(Character& mario, float deltaTime) override;
	void Exit(Character& mario) override;
};