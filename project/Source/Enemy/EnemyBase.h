#pragma once
#include "DxLib.h"

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	virtual EnemyBase* Clone() = 0;

	void SetTransform(VECTOR pos, VECTOR rot, VECTOR scale)
	{
		m_Pos = pos; m_Rot = rot; m_Scale = scale;
	}
	void SetPos(VECTOR pos) { m_Pos = pos; }

private:
	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
};

