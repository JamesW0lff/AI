#include "StalkingEnemy.h"
#include "EnemyStates.h"
#include "Player.h"
#include "SCVEnemy.h"

// ======= SINGLETON =======
extern Player player;
extern SCVEnemy scvEnemy;

#pragma region NAMESPACE
namespace
{

}
#pragma endregion

#pragma region LOAD
void StalkingEnemy::Load()
{
	mStateMachine = std::make_unique<AI::StateMachine<StalkingEnemy>>(*this);

	mStateMachine->AddState<Idle>();
	mStateMachine->AddState<SeekPlayer>();
	mStateMachine->AddState<LocatePlayer>();
	mStateMachine->AddState<ChasePlayer>();
	mStateMachine->AddState<AttackPlayer>();

	ChangeState(EnemyState::Idle);

	mEnemyTextureId = X::LoadTexture("nemesis_8bit.png");
	mEnemySoundId = X::LoadSound("nemesis_stars.wav");

	screenWidth = X::GetScreenWidth();
	screenHeight = X::GetScreenHeight();

	mEnemyPosition = { screenWidth * 0.5f,screenHeight * 0.5f };
}
#pragma endregion

#pragma region UNLOAD
void StalkingEnemy::Unload()
{
	mStateMachine.reset();

	mEnemyTextureId = 0;

	mEnemyPosition = X::Math::Vector2::Zero();
	mTarget = X::Math::Vector2::Zero();

	screenWidth = 0.0f;
	screenHeight = 0.0f;
}
#pragma endregion

#pragma region UPDATE
void StalkingEnemy::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
	
	if (mIsActive)
	{
		if (X::Math::Intersect(player.GetPlayerCollider(), GetEnemyCollider()))
			ChangeState(EnemyState::AttackPlayer);
		else if (X::Math::Intersect(player.GetPlayerCollider(), GetEnemyRange()))
			ChangeState(EnemyState::ChasePlayer);
	}
}
#pragma endregion

#pragma region RENDER
void StalkingEnemy::Render()
{
	if (mIsActive)
	{
		X::DrawSprite(mEnemyTextureId, mEnemyPosition, X::Pivot::Center);
		X::DrawScreenCircle(GetEnemyCollider(), X::Colors::DarkCyan);
		X::DrawScreenCircle(GetEnemyRange(), X::Colors::DarkGreen);
	}
}
#pragma endregion

#pragma region NEARBY PLAYER
void StalkingEnemy::NearbyPlayer()
{
	if (!X::Math::Intersect(player.GetPlayerCollider(), GetEnemyRange()))
	{
		SetEnemyActive(true);
		scvEnemy.SetEnemyActive(false);
		X::Math::Vector2 nemesisPos = GetPosition();
		scvEnemy.SetPosition(nemesisPos);
		ChangeState(EnemyState::SeekPlayer);
	}
		
}
#pragma endregion

#pragma region CHANGE STATE
void StalkingEnemy::ChangeState(EnemyState nextState)
{
	if (nextState == EnemyState::LocatePlayer)
		X::PlaySoundOneShot(mEnemySoundId);

	mStateMachine->ChangeState((size_t)nextState);
}
#pragma endregion