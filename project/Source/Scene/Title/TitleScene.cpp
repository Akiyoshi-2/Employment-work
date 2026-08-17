#include "DxLib.h"
#include "TitleScene.h"
#include "../SceneManager.h"
#include "../Play/PlayScene.h"
#include "../../Input/Input.h"
#include "../../Camera/CameraManager.h"


TitleScene::TitleScene() : SceneBase()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Init()
{

}

void TitleScene::Load()
{

}

void TitleScene::Start()
{

}

void TitleScene::Step()
{
	if (Input::IsTriggerKey(Input::KEY_Z))
	{
		SceneManager::GetInstance()->ChangeScene(PLAY);
	}
}

void TitleScene::Update()
{

}

void TitleScene::Draw()
{
	DrawString(0, 0, "タイトルシーン", GetColor(255, 255, 255));
	DrawString(0, 20, "Zキーでゲームシーン", GetColor(255, 255, 255));
}

void TitleScene::Fin()
{

}