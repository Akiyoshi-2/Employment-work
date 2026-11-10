#include "ItemBase.h"
#include "../Collision/CollisionAABB.h"
#include "../StageObject/StageObject.h"
#include "../StageObject/StageObjectManager.h"
#include "../MyMath/MyMath.h"


ItemBase::ItemBase()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_PrevPos = VGet(0.0f, 0.0f, 0.0f);

	m_AABB = nullptr;
}

ItemBase::~ItemBase()
{
	Fin();
}

void ItemBase::Update()
{
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void ItemBase::Draw()
{
	MV1DrawModel(m_Handle);

	// 当たり判定描画
	if (m_AABB != nullptr)
	{
		m_AABB->Draw();
	}
}

void ItemBase::Fin()
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



bool ItemBase::CheckHitStage(VECTOR nextPos)
{
	if (m_AABB == nullptr) return false;

	CollisionAABB probe;

	probe.SetTargetPos(&nextPos);
	probe.SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	probe.SetSize(m_AABB->GetSize());

	// ステージオブジェクトの取得
	const auto& stageObjects = StageObjectManager::GetInstance()->GetStageObjects();
	for (auto obj : stageObjects)
	{
		if (obj == nullptr) continue;

		const CollisionAABB* objAABB = obj->GetAABB();

		if (objAABB == nullptr) continue;

		if (probe.CheckAABB(objAABB))
		{
			return true;
		}
	}
	return false;
}