#pragma once 
#include "../EnemyBase.h"
#include "../../Bullet/BulletManager.h"

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

	BulletManager* m_BulletManager;

	float m_SearchRange;
	float m_ShootInterval;
	float m_ShootTimer;

	float m_TrackDirection = 1.0f;
	
	bool CheckShootingEnemyFloor(VECTOR nextPos);

	void Shoot(VECTOR playerPos);
};

