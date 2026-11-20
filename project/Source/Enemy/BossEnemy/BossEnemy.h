#pragma once
#include "../EnemyBase.h"

class BossEnemy : public EnemyBase
{
public:
	BossEnemy();
	~BossEnemy();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	// EnemyBase* Clone() override;

	void OnHitPlayer() override;

private:
	enum BOSS_ENEMY_MODE
	{
		BOSS_MODE_NORMAL,
		BOSS_ENEMY_RAGE
	};

	bool m_IsGround;

	static constexpr float MOVE_SPEED = 0.3;
};
