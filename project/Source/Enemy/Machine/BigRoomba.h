#pragma once
#include "../EnemyBase.h"

class BigRoomba : public EnemyBase
{
public:
	BigRoomba();
	virtual ~BigRoomba();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	EnemyBase* Clone() override;

private:
	int m_HP;
};