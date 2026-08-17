#include"DxLib.h"
#include "CollisionAABB.h"
#include "../MyMath/MyMath.h"


CollisionAABB::CollisionAABB()
{
	m_TargetPos = nullptr;
	m_LocalPos = VGet(0.0f, 0.0f, 0.0f);
	m_Size = VGet(0.0f, 0.0f, 0.0f);
}

CollisionAABB::~CollisionAABB()
{
}

void CollisionAABB::Draw()
{
	if (m_TargetPos == nullptr)
	{
		return;
	}

	// デバッグ用当たり判定描画
	VECTOR posA, posB;
	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);

	posA.x = centerPos.x - m_Size.x * 0.5f;
	posA.y = centerPos.y - m_Size.y * 0.5f;
	posA.z = centerPos.z - m_Size.z * 0.5f;

	posB.x = centerPos.x + m_Size.x * 0.5f;
	posB.y = centerPos.y + m_Size.y * 0.5f;
	posB.z = centerPos.z + m_Size.z * 0.5f;

	DrawCube3D(posA, posB, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
}

bool CollisionAABB::CheckAABB(CollisionAABB* other)
{
	if (m_TargetPos == nullptr)
	{
		return false;
	}

	VECTOR centerPos = MyMath::VecAdd(*m_TargetPos, m_LocalPos);
	VECTOR otherCenterPos = MyMath::VecAdd(other->GetTargetPos(), other->GetLocalPos());
	VECTOR otherSize = other->GetSize();

	// 自身のボックス各面の値
	float left		= centerPos.x - m_Size.x * 0.5;
	float right		= centerPos.x + m_Size.x * 0.5;
	float top		= centerPos.y - m_Size.y * 0.5;
	float bottom	= centerPos.y + m_Size.y * 0.5;
	float front		= centerPos.z - m_Size.z * 0.5;
	float back		= centerPos.z + m_Size.z * 0.5;

	// 対象のボックス各面の値
	float otherLeft		= otherCenterPos.x - otherSize.x * 0.5;
	float otherRight	= otherCenterPos.x + otherSize.x * 0.5;
	float otherTop		= otherCenterPos.y - otherSize.y * 0.5;
	float otherBottom	= otherCenterPos.y + otherSize.y * 0.5;
	float otherFront	= otherCenterPos.z - otherSize.z * 0.5;
	float otherBack		= otherCenterPos.z + otherSize.z * 0.5;

	//当たり判定
	if (left <= otherRight && right >= otherLeft &&
		top <= otherBottom && bottom >= otherTop &&
		front <= otherBack && back >= otherFront)
	{
		return true;
	}

	return false;
}