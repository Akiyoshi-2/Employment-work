#include "EnemyManager.h"
#include "../Enemy/Machine/BigRoomba.h"
#include "../Enemy/Machine/BombEnemy.h"
#include "../Collision/CollisionAABB.h"
#include "../Bullet/BulletManager.h"
#include "../Bullet/BulletBase.h"


EnemyManager* EnemyManager::m_Instance = nullptr;

EnemyManager::EnemyManager()
{
	// ‹@ŠB˜f¯‚Ì“G
	for (int i = 0; i < MACHINE_ENEMY_MAX; i++)
	{
		m_OriginalMachineEnemy[i] = nullptr;
	}
	// ƒWƒƒƒ“ƒOƒ‹˜f¯‚Ì“G
	for (int i = 0; i < JUNGLE_ENEMY_MAX; i++)
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
	m_OriginalMachineEnemy[M_ENEMY_00] = new BigRoomba();
	m_OriginalMachineEnemy[M_ENEMY_00]->Init();

	m_OriginalMachineEnemy[M_ENEMY_01] = new BombEnemy();
	m_OriginalMachineEnemy[M_ENEMY_01]->Init();
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
	for (auto it = m_EnemyList.begin(); it != m_EnemyList.end();)
	{
		EnemyBase* enemy = *it;

		if (enemy == nullptr)
		{
			it = m_EnemyList.erase(it);
			continue;
		}

		enemy->Step();

		if (enemy->IsFinished())
		{
			delete enemy;
			it = m_EnemyList.erase(it);
		}
		else
		{
			++it;
		}
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
	case M_ENEMY_00:
		enemy = m_OriginalMachineEnemy[M_ENEMY_00]->Clone();
		break;

	case M_ENEMY_01:
		enemy = m_OriginalMachineEnemy[M_ENEMY_01]->Clone();
		break;
	/*case M_ENEMY_02:
		enemy = m_OriginalMachineEnemy[M_ENEMY_02]->Clone();
		break;*/
	}

	if (enemy)
	{
		enemy->Init();
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

bool EnemyManager::CheckHitPlayer(const CollisionAABB* playerAABB) const
{
	if (playerAABB == nullptr)
	{
		return false;
	}
	
	bool isHit = false;

	for (auto enemy : m_EnemyList)
	{
		if (enemy == nullptr) continue;
		
		CollisionAABB* enemyAABB = enemy->GetCollisionAABB();

		if (enemyAABB == nullptr) continue;

		if (playerAABB->CheckAABB(enemyAABB))
		{
			enemy->OnHitPlayer();
			isHit = true;
		}

	}

	return isHit;
}

void EnemyManager::CheckHitPlayerBullet()
{
	BulletManager* bulletManager = BulletManager::GetInstance();

	if (bulletManager == nullptr) return;

	const auto& bullets = bulletManager->GetBullets();

	for (auto bullet : bullets)
	{
		if (bullet == nullptr || bullet->IsDead()) continue;

		CollisionAABB* bulletAABB = bullet->GetCollisionAABB();

		if (bulletAABB == nullptr) continue;

		for (auto enemy : m_EnemyList)
		{
			if (enemy == nullptr || enemy->IsDefeated()) continue;

			CollisionAABB* enemyAABB = enemy->GetCollisionAABB();

			if (enemyAABB == nullptr) continue;

			if (bulletAABB->CheckAABB(enemyAABB))
			{
				bullet->SetDead();

				enemy->TakeDamage(1);

				break;
			}
		}
	}
}