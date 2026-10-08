#include "EnemyManager.h"
#include "../Enemy/Machine/BigRoomba.h"


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
	// ‹@ŠB˜f¯‚Ì“G
	m_OriginalMachineEnemy[MACHINE_ENEMY_00] = new BigRoomba();
	m_OriginalMachineEnemy[MACHINE_ENEMY_00]->Init();
}

void EnemyManager::Load()
{
	for (int i = 0; i < MACHINE_ENEMY_MAX; i++)
	{
		if (m_OriginalMachineEnemy[i])
		{
			m_OriginalMachineEnemy[i]->Load();
		}
	}
}

void EnemyManager::Start()
{
	for (auto& enemy : m_EnemyList)
	{
		enemy->Start();
	}
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

	// ƒNƒ[ƒ“Œ³‚ğíœ
	// ‹@ŠB˜f¯‚Ì“G
	for (int i = 0; i < MACHINE_ENEMY_MAX; i++)
	{
		if (m_OriginalMachineEnemy[i])
		{
			delete m_OriginalMachineEnemy[i];
			m_OriginalMachineEnemy[i] = nullptr;
		}
	}
}

EnemyBase* EnemyManager::CreateEnemy(int id)
{
	EnemyBase* enemy = nullptr;

	switch (id)
	{
	case MACHINE_ENEMY_00:
		enemy = m_OriginalMachineEnemy[MACHINE_ENEMY_00]->Clone();
		break;

	case MACHINE_ENEMY_01:
		enemy = m_OriginalMachineEnemy[MACHINE_ENEMY_01]->Clone();
		break;
	case MACHINE_ENEMY_02:
		enemy = m_OriginalMachineEnemy[MACHINE_ENEMY_02]->Clone();
		break;
	}

	if (enemy)
	{
		m_EnemyList.push_back(enemy);
	}

	return enemy;
}

EnemyBase* EnemyManager::CreateEnemy(int id, VECTOR pos, VECTOR rot, VECTOR scale)
{
	EnemyBase* enemy = CreateEnemy(id);
	if (enemy)
	{
		enemy->SetTransform(pos, rot, scale);
	}
	return enemy;
}