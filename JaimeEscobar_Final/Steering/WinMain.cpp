#include <AI.h>
#include <XEngine.h>
#include <ImGui/Inc/imgui.h>

#include "SCV.h"

#pragma region GLOBALS
SCV scv;
	
float gWanderDistance = 100.0f;
float gWanderRadius = 60.0f;
float gWanderJitter = 10.0f;
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
	scv.Load();
}
#pragma endregion

#pragma region GAME LOOP
bool GameLoop(float deltaTime)
{
	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		scv.destination.x = static_cast<float>(X::GetMouseScreenX());
		scv.destination.y = static_cast<float>(X::GetMouseScreenY());
	}

	scv.Update(deltaTime);
	scv.Render();

	ShowTuningUI();

	X::DrawScreenDiamond(scv.destination, 10.0f, X::Colors::Red);

	return X::IsKeyPressed(X::Keys::ESCAPE);
}
#pragma endregion

#pragma region GAME CLEANUP
void GameCleanup()
{
	scv.Unload();
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