#pragma once
#include "SceneBase.h"
#include "SceneParameter.h"

class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	static void CretateInstance() { if (!m_Instance) m_Instance = new SceneManager; }
	static SceneManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance)delete m_Instance; m_Instance = nullptr; }

	void Init();
	void Update();
	void Fin();

	void ChangeScene(SceneType type);

private:
	void InitScene();
	void LoadScene();
	void StartScene();
	void LoopScene();
	void FinScene();

	void CreateScene(SceneType type);

private:
	static SceneManager* m_Instance;

	SceneBase* m_NowScene;

	SceneState m_State;

	SceneType m_NextScene;

	void (SceneManager::* m_StateFunc[SCENE_STATE_MAX])(void);
	
};
