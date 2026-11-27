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
	void Draw();
	
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

	// 攻撃関数ポインタ
	using AttackFunction = void (BossAttack::*)(VECTOR bossPos);

	BOSS_ATTACK_TYPE m_AttackType;
	BOSS_ATTACK_STATE m_AttackState;

	float m_AttackInterval;
	float m_AttackTimer;

	int m_ShotCount;

	// ロックオン用
	VECTOR m_BossPos;
	VECTOR m_LockOnDirection;
	VECTOR m_LockOnTargetPos;

	// ロックオン時間
	float m_LockOnTimer;

	// 実行中の攻撃関数
	AttackFunction m_CurrentAttack;

	// バースト射撃
	void BurstAttack(VECTOR bossPos);

	// ロックオンレーザー
	void LockOnAttack(VECTOR bossPos);

	// ボスの種類ごとの処理
	void MachineBossAttack(VECTOR bossPos);
	void JungleBossAttack();
	void LavaBossAttack();
	void PollutionBossAttack();
	
};

