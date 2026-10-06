#include "EnemyManager.h"


EnemyManager* EnemyManager::m_Instance = nullptr;

EnemyManager::EnemyManager()
{
	// ‹@ŠB˜f¯‚Ì“G
	for (int i = 0; i < MACHINE_ENEMY_MAX; i++)
	{
		m_OriginalMachineEnemy[i] = nullptr;
	}
	// ƒWƒƒƒ“ƒOƒ‹˜f¯‚Ì“G
	for (int i = 0; i < JANGLE_ENEMY_MAX; i++)
	{
		m_OriginalJungleEnemy[i] = nullptr;
	}
	// —nŠâ˜f¯‚Ì“G
	for (int i = 0; i < LAVA_ENEMY_MAX; i++)
	{
		m_OriginalLavaEnemy[i] = nullptr;
	}
	// ‰˜õ˜f¯‚Ì“G
	for (int i = 0; i < POLLUTION_ENEMY_MAX; i++)
	{
		m_OriginalPollutionEnemy[i] = nullptr;
	}
}

EnemyManager::~EnemyManager()
{
	Fin();
}

void EnemyManager::Init()
{
}

void EnemyManager::Load()
{
}

void EnemyManager::Start()
{
}

void EnemyManager::Step()
{
	for (auto& enemy : m_EnemyList)
	{
		enemy->Step();
	}
}

void EnemyManager::Update()
{
	for (auto& enemy : m_EnemyList)
	{
		enemy->Update();
	}
}

void EnemyManager::Draw()
{
	for (auto& enemy : m_EnemyList)
	{
		enemy->Draw();
	}
}

void EnemyManager::Fin()
{
	for (auto& enemy : m_EnemyList)
	{
		delete enemy;
	}
	m_EnemyList.clear();
}