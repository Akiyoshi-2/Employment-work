#pragma once
#include "DxLib.h"
#include "EnemyBase.h"
#include "EnemyParameter.h"
#include <list>

class EnemyManager
{
public:
	EnemyManager();
	~EnemyManager();

	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	static void CreateInstance() { if (!m_Instance) m_Instance = new EnemyManager; }
	static EnemyManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	EnemyBase* CreateEnemy(int id);
	EnemyBase* CreateEnemy(int id, VECTOR pos, VECTOR rot, VECTOR scale);

private:
	static EnemyManager* m_Instance;

	EnemyBase* m_OriginalMachineEnemy[MACHINE_ENEMY_MAX];
	EnemyBase* m_OriginalJungleEnemy[JANGLE_ENEMY_MAX];
	EnemyBase* m_OriginalLavaEnemy[LAVA_ENEMY_MAX];
	EnemyBase* m_OriginalPollutionEnemy[POLLUTION_ENEMY_MAX];

	std::list<EnemyBase*> m_EnemyList;
};
