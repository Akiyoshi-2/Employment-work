#pragma once
#include "DxLib.h"

class CollisionAABB
{
public:
	CollisionAABB();
	~CollisionAABB();

	// •`‰æ
	void Draw();

	void SetTargetPos(VECTOR* targetPos) { m_TargetPos = targetPos; }
	void SetLocalPos(VECTOR localPos) { m_LocalPos = localPos; }
	void SetSize(VECTOR size) { m_Size = size; }

	VECTOR GetTargetPos() const { return *m_TargetPos; }
	VECTOR GetLocalPos() const { return m_LocalPos; }
	VECTOR GetSize() const { return m_Size; }

	VECTOR GetMin() const;
	VECTOR GetMax() const;

	bool CheckAABB(const CollisionAABB* other) const;
	
private:
	VECTOR* m_TargetPos;
	VECTOR m_LocalPos;
	VECTOR m_Size;
};
