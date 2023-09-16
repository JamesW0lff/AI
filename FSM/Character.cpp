#include "Character.h"
#include "CharacterStates.h"

#pragma region LOAD
void Character::Load()
{	 
	// make this state machine to control "me"
	mStateMachine = std::make_unique<AI::StateMachine<Character>>(*this);
	
	mStateMachine->AddState<MoveToMushroomState>();
	mStateMachine->AddState<EatMushroomState>();
	
	ChangeState(EnemyState::MoveToMushroom);

	mCharacterTextureId = X::LoadTexture("mario_idle_01.png");
}	
#pragma endregion
	 
#pragma region UNLOAD
void Character::Unload()
{	 
	mCharacterTextureId = 0;
	mStateMachine.reset();
}	 
#pragma endregion
	 
#pragma region UPDATE
void Character::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}
#pragma endregion
	 
#pragma region RENDER
void Character::Render()
{
	X::DrawSprite(mCharacterTextureId, mCharacterPosition);
}
#pragma endregion

#pragma region CHANGE STATE
void Character::ChangeState(EnemyState nextState)
{
	mStateMachine->ChangeState((size_t)nextState);
}
#pragma endregion