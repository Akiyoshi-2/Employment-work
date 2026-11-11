#pragma once
#include "DxLib.h"
#include "ItemParameter.h"
#include <vector>

class CollisionAABB;
class StageObject;

class ItemBase
{
public:
	ItemBase();
	virtual~ItemBase();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	virtual ItemBase* Clone() = 0;

	void SetTransform(VECTOR pos, VECTOR rot, VECTOR scale)
	{
		m_Pos = pos;
		m_Rot = rot;
		m_Scale = scale;
	}

	virtual void PlayerGetItem() {}

	virtual void ItemDrop(VECTOR pos) {}

protected:
	int m_Handle;

	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
	VECTOR m_PrevPos;

	ITEM_ID m_ItemID;

	CollisionAABB* m_AABB;

	bool CheckHitStage(VECTOR nextPos);
};

