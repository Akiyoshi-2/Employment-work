#pragma once
#include "../EnemyBase.h"

class BombEnemy : public EnemyBase
{
public:
	BombEnemy();
	~BombEnemy() override;

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	EnemyBase* Clone() override;
		 
	void OnHitPlayer() override;

	bool IsFinished() const override
	{
		return m_IsExploded || IsDefeated();
	}

private:
	enum BombState
	{
		BOMB_STATE_WAIT,
		BOMB_STATE_CHASE,
		BOMB_STATE_EXPLODED
	};

	BombState m_State;
	bool m_IsExploded;

	float m_SearchRange;

	void ChangeModel(const char* modelPath);

	void Explode();
};

