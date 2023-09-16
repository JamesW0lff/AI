#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

#include "AI.h"

#include "Player.h"
#include "TileMap.h"

#pragma region GLOBALS
Player player;
#pragma endregion

#pragma region GAME INIT
void GameInit()
{
	// ======= LOAD =======
	player.Load();
}
#pragma endregion

#pragma region GAME LOOP
bool GameLoop(float deltaTime)
{
	// ======= UPDATE =======
	player.Update(deltaTime);

	// ======= RENDER =======
	player.Render();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}
#pragma endregion

#pragma region GAME CLEANUP
void GameCleanup()
{
	// ======= UNLOAD =======
	player.Unload();
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