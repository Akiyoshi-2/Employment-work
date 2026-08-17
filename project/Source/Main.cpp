#include "DxLib.h"
#include "../Source/Input/Input.h"
#include "../Source/Scene/SceneManager.h"
#include "../Source/FPS/FPS.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_  HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	// ウィンドウモードON
	ChangeWindowMode(TRUE);

	SetGraphMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32);

	if (DxLib_Init() == -1)	
	{
		return -1;
	}

	SetDrawScreen(DX_SCREEN_BACK);

	// シーンマネージャー
	SceneManager::CretateInstance();
	SceneManager* sceneManager = SceneManager::GetInstance();
	sceneManager->Init();

	Input::Init();

	FPSSystem::Init();

	// メインループ
	while (ProcessMessage() >= 0)
	{
		Sleep(1);

		ClearDrawScreen();

		// 入力更新
		Input::Update();

		// シーン更新
		sceneManager->Update();

		Input::Draw();

		FPSSystem::Update();

		FPSSystem::Draw();

		if (CheckHitKey(KEY_INPUT_ESCAPE)) break;

		ScreenFlip();
	}

	SceneManager::DeleteInstance();


	Input::Fin();

	DxLib_End();

	return 0;				
}
