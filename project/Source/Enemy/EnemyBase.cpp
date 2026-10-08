#include "EnemyBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionAABB.h"
#include <stdio.h>

EnemyBase::EnemyBase()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_AABB = nullptr;

	m_Surface = ENEMY_SURFACE_FLOOR;
	m_Dir = ENEMY_DIR_LEFT;
}

EnemyBase::~EnemyBase()
{
	Fin();
}

void EnemyBase::Update()
{
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void EnemyBase::Draw()
{
	if (m_Handle == 0)
	{
		printfDx("Draw ERROR: handle=0\n");
		return;
	}
	MV1DrawModel(m_Handle);
}

void EnemyBase::Fin()
{
	if (m_AABB)
	{
		delete m_AABB;
		m_AABB = nullptr;
	}

	if (m_Handle != 0)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = 0;
	}
}