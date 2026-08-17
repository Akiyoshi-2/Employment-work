#include "DxLib.h"
#include "CollisionSphere.h"
#include "../MyMath/MyMath.h"


CollisionSphere::CollisionSphere()
{
	m_TargetPos = nullptr;
	m_LocalPos = VGet(0.0f, 0.0f, 0.0f);
	m_Radius = 0.0f;
}

CollisionSphere::~CollisionSphere()
{
}

void CollisionSphere::Draw()
{
	// デバッグ用当たり判定描画
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	DrawSphere3D(centerPos, m_Radius, 16, 
		GetColor(255, 255, 255), GetColor(255, 255, 255), false);
}

VECTOR CollisionSphere::GetWorldPos()
{
	return MyMath::VecAdd(*m_TargetPos, m_LocalPos);
}

bool CollisionSphere::CheakSphere(CollisionSphere* other)
{
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	VECTOR otherCenterPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
	float otherRadius = other->GetRadius();

	VECTOR vec = MyMath::VecCreate(centerPos, otherCenterPos);
	float distance = MyMath::VecLong(vec);

	if (distance <= m_Radius + otherRadius)
	{
		return true;
	}

	return false;
}