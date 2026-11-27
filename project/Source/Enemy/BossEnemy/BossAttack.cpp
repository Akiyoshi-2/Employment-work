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

	m_BossPos = VGet(0.0f, 0.0f, 0.0f);
	m_LockOnDirection = VGet(0.0f, 0.0f, 1.0f);
	m_LockOnTargetPos = VGet(0.0f, 0.0f, 0.0f);

	m_LockOnTimer = 0.0f;
	
	m_CurrentAttack = nullptr;
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

	m_BossPos = VGet(0.0f, 0.0f, 0.0f);
	m_LockOnDirection = VGet(0.0f, 0.0f, 1.0f);
	m_LockOnTargetPos = VGet(0.0f, 0.0f, 0.0f);

	m_LockOnTimer = 0.0f;

	m_CurrentAttack = nullptr;
}

void BossAttack::Step(VECTOR bossPos)
{
	m_BossPos = bossPos;

	// 現在の攻撃関数
	MachineBossAttack(bossPos);

	// 攻撃状態の共通管理
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
		// ロックオン攻撃の場合
		if (m_AttackType == ATTACK_LOCKON)
		{
			Player* player = PlayerManager::GetInstance()->GetPlayer();

			if (player != nullptr)
			{
				m_LockOnTargetPos = player->GetPos();

				VECTOR direction = VSub(m_LockOnDirection, bossPos);

				float distance = VSize(direction);

				if (distance > 0.001f)
				{
					m_LockOnDirection = VScale(direction, 1.0f / distance);
				}
			}

			// ロックオン時間
			m_LockOnTimer += 1.0f / 60.0f;

			if (m_LockOnTimer >= 1.0f)
			{
				m_LockOnTimer = 0.0f;
				m_AttackTimer = 0.0f;

				m_AttackState = ATTACK_EXECUTE;
			}
		}
		else
		{
			m_AttackTimer = 0.0f;
			m_AttackState = ATTACK_EXECUTE;
		}
		break;

	case BossAttack::ATTACK_EXECUTE:
		m_AttackTimer += 1.0f / 60.0f;

		// バースト射撃の間隔
		if (m_AttackTimer >= 0.15f)
		{
			m_AttackTimer = 0.0f;

			// 関数ポインタで攻撃を実行
			if (m_CurrentAttack != nullptr)
			{
				(this->*m_CurrentAttack)(bossPos);
			}

			m_ShotCount++;

			if (m_ShotCount >= 5)
			{
				m_AttackState = ATTACK_END;
			}
		}
		break;

	case BossAttack::ATTACK_END:
		m_AttackTimer = 0.0f;
		m_LockOnTimer = 0.0f;

		// ランダムに次の攻撃へ切り替える
		if (0)
		{

		}

		m_AttackState = ATTACK_WAIT;
		break;
	}
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
		m_CurrentAttack = &BossAttack::BurstAttack;
		break;

	case BossAttack::ATTACK_LOCKON:
		m_CurrentAttack = &BossAttack::LockOnAttack;
		break;

	case BossAttack::ATTACK_MISSILE:
		m_CurrentAttack = nullptr;
		break;

	case BossAttack::ATTACK_WIDE_LASER:
		m_CurrentAttack = nullptr;
		break;
	}
}

void BossAttack::BurstAttack(VECTOR bossPos)
{
Player* player = PlayerManager::GetInstance()->GetPlayer();
}

void BossAttack::LockOnAttack(VECTOR bossPos)
{
	
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