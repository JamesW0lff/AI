#pragma once

#include <AI.h>
#include <XEngine.h>

#include "StalkingEnemy.h"

#pragma region IDLE
class Idle : public AI::State<StalkingEnemy>
{
public:

	void Enter(StalkingEnemy& nemesis) override;
	void Update(StalkingEnemy& nemesis, float deltaTime) override;
	void Exit(StalkingEnemy& nemesis) override;
};
#pragma endregion

#pragma region SEEK PLAYER
class SeekPlayer : public AI::State<StalkingEnemy>
{
public:

	void Enter(StalkingEnemy& nemesis) override;
	void Update(StalkingEnemy& nemesis, float deltaTime) override;
	void Exit(StalkingEnemy& nemesis) override;
};
#pragma endregion

#pragma region LOCATE PLAYER
class LocatePlayer : public AI::State<StalkingEnemy>
{
public:

	void Enter(StalkingEnemy& nemesis) override;
	void Update(StalkingEnemy& nemesis, float deltaTime) override;
	void Exit(StalkingEnemy& nemesis) override;
};
#pragma endregion

#pragma region CHASE PLAYER
class ChasePlayer : public AI::State<StalkingEnemy>
{
public:

	void Enter(StalkingEnemy& nemesis) override;
	void Update(StalkingEnemy& nemesis, float deltaTime) override;
	void Exit(StalkingEnemy& nemesis) override;
};
#pragma endregion

#pragma region ATTACK PLAYER
class AttackPlayer : public AI::State<StalkingEnemy>
{
public:

	void Enter(StalkingEnemy& nemesis) override;
	void Update(StalkingEnemy& nemesis, float deltaTime) override;
	void Exit(StalkingEnemy& nemesis) override;
};
#pragma endregion