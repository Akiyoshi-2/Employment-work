#include "DxLib.h"
#include "GameOver.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"
#include "../../Scene/Title/TitleScene.h"


GameOver::GameOver()
{
}

GameOver::~GameOver()
{
}

void GameOver::Init()
{

}

void GameOver::Load()
{

}

void GameOver::Start()
{

}

void GameOver::Step()
{
	if (Input::IsTriggerKey(Input::KEY_Z))
	{
		SceneManager::GetInstance()->ChangeScene(TITLE);
	}
}

void GameOver::Update()
{

}

void GameOver::Draw()
{
	DrawString(0, 0, "ゲームオーバーシーン", GetColor(255, 255, 255));
	DrawString(0, 20, "Zキーでタイトルシーン", GetColor(255, 255, 255));
}

void GameOver::Fin()
{

}