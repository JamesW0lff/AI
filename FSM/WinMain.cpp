#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

#include "Character.h"
#include "MushroomWorld.h"

#pragma region GLOBALS
Character character;
#pragma endregion

#pragma region GAME INIT
void GameInit()
{
	character.Load();
	MushroomWorld::Get().Load();
}
#pragma endregion

#pragma region GAME LOOP
bool GameLoop(float deltaTime)
{
	character.Update(deltaTime);

	MushroomWorld::Get().Render();
	character.Render();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}
#pragma endregion

#pragma region GAME CLEANUP
void GameCleanup()
{
	character.Unload();
	MushroomWorld::Get().Unload();
}
#pragma endregion

#pragma region WIN MAIN
int WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("xconfig.json");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}
#pragma endregion