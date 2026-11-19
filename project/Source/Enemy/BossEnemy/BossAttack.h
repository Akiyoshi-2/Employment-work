#pragma once
#include "../EnemyBase.h"
#include "../EnemyParameter.h"

class BossAttack
{
public:
	BossAttack();
	~BossAttack();

private:
	void MachineBossAttack();
	void JungleBossAttack();
	void LavaBossAttack();
	void PollutionBossAttack();

	static constexpr float MOVE_SPEED = 0.3;

	float m_AttackInterval;
	float m_AttackTimer;


};

