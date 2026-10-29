#pragma once 
#include "../EnemyBase.h"

class ShootingEnemy : public EnemyBase
{
public:
	ShootingEnemy();
	virtual ~ShootingEnemy();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	EnemyBase* Clone() override;

	void OnHitPlayer() override;

private:
	enum ShootingState
	{
		SHOOTING_NORMAL,
		SHOOTING_TRACK,
	};

	ShootingState m_State = SHOOTING_NORMAL;

	float m_SearchRange;
	float m_ShootRange;
	float m_ShootInterval;
	float m_ShootTimer;

	float m_TrackDirection = 1.0f;
	
	void Shoot(VECTOR playerPos);

};

