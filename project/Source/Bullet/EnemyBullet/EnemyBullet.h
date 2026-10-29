#pragma once
#include "../BulletBase.h"

class EnemyBullet : public BulletBase
{
public:
	EnemyBullet();
	virtual ~EnemyBullet();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	
	void SetDirection(VECTOR direction);
	void SetPosition(VECTOR pos);

private:

};

