#include "DxLib.h"
#include "ClearScene.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"

ClearScene::ClearScene()
{
}

ClearScene::~ClearScene()
{
}

void ClearScene::Init()
{

}

void ClearScene::Load()
{

}

void ClearScene::Start()
{

}

void ClearScene::Step()
{

}

void ClearScene::Update()
{

}

void ClearScene::Draw()
{
	DrawString(0, 0, "クリアシーン", GetColor(255, 255, 255));
	DrawString(0, 20, "Zキーでタイトルシーン", GetColor(255, 255, 255));
}

void ClearScene::Fin()
{

}