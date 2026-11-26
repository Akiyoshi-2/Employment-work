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

	void SetMoveRange(float minX, float maxX);

private:
	enum BOSS_ENEMY_MODE
	{
		BOSS_MODE_NORMAL,
		BOSS_ENEMY_RAGE
	};
	BOSS_ENEMY_MODE m_Mode;

	// ˆÚ“®”ÍˆÍ
	float m_MoveMinX;
	float m_MoveMaxX;
	
	// ˆÚ“®•ûŒü
	float m_MoveDirX;

	// •‚—V
	float m_FloatBaseY;
	float m_FloatTimer;

	static constexpr int MAX_HP = 400;
	static constexpr float RAGE_HP_RATE = 0.5f;
	
	static constexpr float MOVE_SPEED = 0.2f;
	static constexpr float RAGE_MOVE_SPEED = 0.35f;

	static constexpr float FLOAT_HEIGHT = 1.0f;
	static constexpr float FLOAT_SPEED = 2.0f;

	BossAttack m_BossAttack;

};
