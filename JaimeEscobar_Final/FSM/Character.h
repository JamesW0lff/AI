#pragma once

#include <AI.h>
#include <XEngine.h>

enum class EnemyState
{
	MoveToMushroom
};

class Character
{
public:

	void Load();
	void Unload();

	void Update(float deltaTime);
	void Render();

	void ChangeState(EnemyState nextState);

	void SetPosition(const X::Math::Vector2& pos) { mCharacterPosition = pos; }
	const X::Math::Vector2& GetPosition() const { return mCharacterPosition; }

	void SetTargetMushroom(size_t index) { mTargetMushroom = index; }
	size_t GetTargetMushroom() const { return mTargetMushroom; }

private:

	std::unique_ptr<AI::StateMachine<Character>> mStateMachine;
	X::TextureId mCharacterTextureId;
	X::Math::Vector2 mCharacterPosition;
	size_t mTargetMushroom = 0;
};