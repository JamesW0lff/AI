#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

#include "AI.h"

#include "TileMap.h"
#include "Player.h"
#include "StalkingEnemy.h"
#include "EnemyStates.h"
#include "SCVEnemy.h"

#pragma region GLOBALS
TileMap tileMap;
Player player;
StalkingEnemy stalkingEnemy;
SCVEnemy scvEnemy;

float gWanderDistance = 100.0f;
float gWanderRadius = 20.0f;
float gWanderJitter = 2.5f;
#pragma endregion

#pragma region SHOW TUNING UI
void ShowTuningUI()
{
	ImGui::Begin("Steering Tuning", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	ImGui::SliderFloat("Wander Distance", &gWanderDistance, 50.0f, 200.0f);
	ImGui::SliderFloat("Wander Radius", &gWanderRadius, 1.0f, 200.0f);
	ImGui::SliderFloat("Wander Jitter", &gWanderJitter, 1.0f, gWanderRadius);
	ImGui::End();
}
#pragma endregion

#pragma region GAME INIT
void GameInit()
{
	// ======= LOAD =======
	tileMap.LoadMap("map.txt");
	tileMap.LoadTiles("tileset.txt");

	player.Load();

	stalkingEnemy.Load();
	scvEnemy.Load();
}
#pragma endregion

#pragma region GAME LOOP
bool GameLoop(float deltaTime)
{
	// ======= UPDATE =======
	player.Update(deltaTime);
	stalkingEnemy.Update(deltaTime);
	scvEnemy.Update(deltaTime);

	// ======= RENDER =======
	tileMap.Render();
	player.Render();
	stalkingEnemy.Render();
	scvEnemy.Render();

	// ======= SHOW UI =======
	// ShowTuningUI();

	return X::IsKeyPressed(X::Keys::ESCAPE);
}
#pragma endregion

#pragma region GAME CLEANUP
void GameCleanup()
{
	// ======= UNLOAD =======
	player.Unload();
	stalkingEnemy.Unload();
	scvEnemy.Unload();
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