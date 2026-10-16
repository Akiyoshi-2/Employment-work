#pragma once
#include "../EnemyBase.h"

class BombEnemy : public EnemyBase
{
public:
	BombEnemy();
	~BombEnemy();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	EnemyBase* Clone() override;
		 
	void OnHitPlayer() override;

private:
	int m_HP;

};
