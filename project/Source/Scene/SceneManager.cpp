#include "SceneManager.h"
#include "Title/TitleScene.h"
#include "Play/PlayScene.h"

SceneManager* SceneManager::m_Instance = nullptr;

SceneManager::SceneManager()
{
	m_NowScene = nullptr;
	m_State = SCENE_STATE_NONE;
	m_NextScene = SCENE_TYPE_NONE;

	for (int i = 0; i < SCENE_STATE_MAX; i++)
	{
		m_StateFunc[i] = nullptr;
	}
}

SceneManager::~SceneManager()
{
	Fin();
}

void SceneManager::Init()
{
	m_StateFunc[INIT] = &SceneManager::InitScene;
	m_StateFunc[LOAD] = &SceneManager::LoadScene;
	m_StateFunc[START] = &SceneManager::StartScene;
	m_StateFunc[LOOP] = &SceneManager::LoopScene;
	m_StateFunc[FIN] = &SceneManager::FinScene;

	CreateScene(TITLE);
	m_State = INIT;
}

void SceneManager::Update()
{
	(this->*m_StateFunc[m_State])();
}

void SceneManager::Fin()
{
	if (m_NowScene)
	{
		delete m_NowScene;
	}
}

void SceneManager::ChangeScene(SceneType type)
{
	m_NextScene = type;
	m_State = FIN;
}

void SceneManager::InitScene()
{
	m_NowScene->Init();
	m_State = LOAD;
}

void SceneManager::LoadScene()
{
	m_NowScene->Load();
	m_State = START;
}

void SceneManager::StartScene()
{
	m_NowScene->Start();
	m_State = LOOP;
}

void SceneManager::LoopScene()
{
	m_NowScene->Step();
	m_NowScene->Update();
	m_NowScene->Draw();
}

void SceneManager::FinScene()
{
	m_NowScene->Fin();

	if (m_NowScene)
	{
		delete m_NowScene;
		
	}

	CreateScene(m_NextScene);

	m_State = INIT;
}

void SceneManager::CreateScene(SceneType type)
{
	switch (type)
	{
	case TITLE:
		m_NowScene = new TitleScene;
		break;
	case PLAY:
		m_NowScene = new PlayScene;
		break;
	/*
	case Clear:
		m_NowScene = new ClearScene;
		break;

	case GameOver:
		m_NowScene = new GameOverScene;
		break;
	*/
	}
}