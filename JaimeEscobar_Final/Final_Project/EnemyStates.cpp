#include "EnemyStates.h"
#include "Player.h"
#include "SCVEnemy.h"

// ======= SINGLETON =======
extern Player player;
extern SCVEnemy scvEnemy;

#pragma region NAMESPACE
namespace
{
	float timer = 0.0f;
	float enemySpeed = 200.0f;
}
#pragma endregion

#pragma region IDLE
#pragma region ENTER
void Idle::Enter(StalkingEnemy& nemesis)
{
	timer = 0.0f;
}
#pragma endregion

#pragma region UPDATE
void Idle::Update(StalkingEnemy& nemesis, float deltaTime)
{
	while (timer < 5.0f)
		timer += deltaTime;

	nemesis.ChangeState(EnemyState::SeekPlayer);
}
#pragma endregion

#pragma region EXIT
void Idle::Exit(StalkingEnemy& nemesis)
{

}
#pragma endregion
#pragma endregion

#pragma region SEEK PLAYER
#pragma region ENTER
void SeekPlayer::Enter(StalkingEnemy& nemesis)
{

}
#pragma endregion

#pragma region UPDATE
void SeekPlayer::Update(StalkingEnemy& nemesis, float deltaTime)
{
	nemesis.SetEnemyActive(false);
	scvEnemy.SetEnemyActive(true);
}
#pragma endregion

#pragma region EXIT
void SeekPlayer::Exit(StalkingEnemy& nemesis)
{
	
}
#pragma endregion
#pragma endregion

#pragma region LOCATE PLAYER
#pragma region ENTER
void LocatePlayer::Enter(StalkingEnemy& nemesis)
{

}
#pragma endregion

#pragma region UPDATE
void LocatePlayer::Update(StalkingEnemy& nemesis, float deltaTime)
{
	auto playerLocation = player.GetLocation();
	// Enemy has arrived to the desire target
	if (X::Math::Distance(nemesis.GetPosition(), playerLocation) < 10.0f)
	{
		nemesis.SetTarget(playerLocation);
		nemesis.NearbyPlayer();
	}
	else
	{
		auto direction = X::Math::Normalize(playerLocation - nemesis.GetPosition());
		auto velocity = direction * enemySpeed;
		nemesis.SetPosition(nemesis.GetPosition() + velocity * deltaTime);
	}
}
#pragma endregion

#pragma region EXIT
void LocatePlayer::Exit(StalkingEnemy& nemesis)
{

}
#pragma endregion
#pragma endregion

#pragma region CHASE PLAYER
#pragma region ENTER
void ChasePlayer::Enter(StalkingEnemy& nemesis)
{

}
#pragma endregion

#pragma region UPDATE
void ChasePlayer::Update(StalkingEnemy& nemesis, float deltaTime)
{
	auto playerPosition = player.GetPosition();
	if (X::Math::Distance(nemesis.GetPosition(), playerPosition) < 10.0f)
	{
		nemesis.SetTarget(playerPosition);
		nemesis.NearbyPlayer();
	}
	else if (X::Math::Intersect(player.GetPlayerCollider(), nemesis.GetEnemyRange()))
	{
		auto direction = X::Math::Normalize(playerPosition - nemesis.GetPosition());
		auto velocity = direction * enemySpeed;
		nemesis.SetPosition(nemesis.GetPosition() + velocity * deltaTime);
	}
	else
	{
		nemesis.ChangeState(EnemyState::SeekPlayer);
	}
}
#pragma endregion

#pragma region EXIT
void ChasePlayer::Exit(StalkingEnemy& nemesis)
{

}
#pragma endregion
#pragma endregion

#pragma region ATTACK PLAYER
#pragma region ENTER
void AttackPlayer::Enter(StalkingEnemy& nemesis)
{
	timer = 0.0f;
}
#pragma endregion

#pragma region UPDATE
void AttackPlayer::Update(StalkingEnemy& nemesis, float deltaTime)
{
	auto getTime = X::GetTime();

	if (timer < getTime)
	{
		player.ReceiveDamage(10);
		timer = getTime + 2.0f;
	}
		
}
#pragma endregion

#pragma region EXIT
void AttackPlayer::Exit(StalkingEnemy& nemesis)
{
	timer = 0.0f;
}
#pragma endregion
#pragma endregion