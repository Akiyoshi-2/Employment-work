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
	
}

void GameOver::Fin()
{

}