#include "BossAttack.h"
#include "BossEnemy.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerManager.h"
#include "../../Bullet/BulletManager.h"
#include "../../Bullet/EnemyBullet/EnemyBullet.h"

BossAttack::BossAttack()
{
	m_AttackType = ATTACK_BURST;
	m_AttackState = ATTACK_WAIT;

	m_AttackInterval = 0;
	m_AttackTimer = 0.0f;

	m_ShotCount = 0;
}

BossAttack::~BossAttack()
{

}

void BossAttack::Init()
{
	m_AttackType = ATTACK_BURST;
	m_AttackState = ATTACK_WAIT;

	m_AttackInterval = 3.0f;
	m_AttackTimer = 0.0f;
	m_ShotCount = 0;
}

void BossAttack::Step(VECTOR bossPos)
{
	MachineBossAttack(bossPos);
}

bool BossAttack::IsMoveStopped() const
{
	// ミサイル攻撃・広範囲レーザー中は停止
	if (m_AttackType == ATTACK_MISSILE || m_AttackType == ATTACK_WIDE_LASER)
	{
		return m_AttackType == ATTACK_MISSILE || m_AttackType == ATTACK_WIDE_LASER;
	}

	return false;
}

void BossAttack::MachineBossAttack(VECTOR bossPos)
{
	switch (m_AttackType)
	{
	case BossAttack::ATTACK_BURST:
		BurstAttack(bossPos);
		break;

	case BossAttack::ATTACK_LOCKON:

		break;

	case BossAttack::ATTACK_MISSILE:

		break;

	case BossAttack::ATTACK_WIDE_LASER:

		break;
	}
}

void BossAttack::BurstAttack(VECTOR bossPos)
{
	switch (m_AttackState)
	{
	case BossAttack::ATTACK_WAIT:
		m_AttackTimer += 1.0f / 60.0f;

		if (m_AttackTimer >= m_AttackInterval)
		{
			m_AttackTimer = 0.0f;
			m_ShotCount = 0;

			m_AttackState = ATTACK_START;
		}
		break;

	case BossAttack::ATTACK_START:
		m_AttackTimer = 0.0f;
		m_ShotCount = 0;

		m_AttackState = ATTACK_EXECUTE;
		break;

	case BossAttack::ATTACK_EXECUTE:
		m_AttackTimer += 1.0f / 60.0f;

		if (m_AttackTimer >= 0.15f)
		{
			m_AttackTimer = 0.0f;

			Player* player = PlayerManager::GetInstance()->GetPlayer();

			if (player != nullptr)
			{
				VECTOR playerPos = player->GetPos();

				VECTOR direction = VSub(playerPos, bossPos);

				float distance = VSize(direction);

				if (distance > 0.001f)
				{
					direction = VScale(direction, 1.0f / distance);
				}
				else
				{
					direction = VGet(0.0f, 0.0f, 1.0f);
				}

				EnemyBullet* bullet = new EnemyBullet();

				bullet->Init();
				bullet->Load();
			}
		}
		break;

	case BossAttack::ATTACK_END:

		break;
	}
}

void BossAttack::JungleBossAttack()
{

}

void BossAttack::LavaBossAttack()
{

}

void BossAttack::PollutionBossAttack()
{

}