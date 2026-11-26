#pragma once
#include "DxLib.h"
#include "../EnemyBase.h"
#include "../EnemyParameter.h"

class BossAttack
{
public:
	BossAttack();
	~BossAttack();

	void Init();
	void Step(VECTOR bossPos);
	
	bool IsMoveStopped() const;

private:
	enum BOSS_ATTACK_TYPE
	{
		ATTACK_BURST,		// 射撃
		ATTACK_LOCKON,		// ロックオンレーザー
		ATTACK_MISSILE,		// ミサイル
		ATTACK_WIDE_LASER,	// 広範囲レーザー
	};

	enum BOSS_ATTACK_STATE
	{
		ATTACK_WAIT,		// 攻撃待機
		ATTACK_START,		// 攻撃開始
		ATTACK_EXECUTE,		// 攻撃実行
		ATTACK_END			// 攻撃終了
	};

	BOSS_ATTACK_TYPE m_AttackType;
	BOSS_ATTACK_STATE m_AttackState;

	float m_AttackInterval;
	float m_AttackTimer;

	int m_ShotCount;

	// ボスの種類ごとの処理
	void MachineBossAttack(VECTOR bossPos);
	void JungleBossAttack();
	void LavaBossAttack();
	void PollutionBossAttack();

	// バースト射撃
	void BurstAttack(VECTOR bossPos);
};

