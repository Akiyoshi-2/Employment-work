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
	bool HasSurfaceAhead(VECTOR nextPos);

	void UpdateRot();

};

