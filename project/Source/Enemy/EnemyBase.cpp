#include "EnemyBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionAABB.h"
#include "../StageObject/StageObject.h"
#include "../StageObject/StageObjectManager.h"
#include <stdio.h>
#include <math.h>

EnemyBase::EnemyBase()
{
	m_HP = 0;
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Rot = VGet(0.0f, 0.0f, 0.0f);
	m_Scale = VGet(1.0f, 1.0f, 1.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_PrevPos = VGet(0.0f, 0.0f, 0.0f);

	m_AABB = nullptr;

	m_Surface = ENEMY_SURFACE_NONE;
	m_Dir = ENEMY_DIR_NONE;
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
	MV1DrawModel(m_Handle);

	// ìñÇΩÇËîªíËï`âÊ
	if (m_AABB != nullptr)
	{
		m_AABB->Draw();
	}
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

void EnemyBase::SetSurfaceFromRotation()
{
	const float HALF_PI = DX_PI_F * 0.5f;
	const float PI = DX_PI_F;

	float rotZ = m_Rot.z;

	// -180ÅãÅ`180ÅãÇ…é˚ÇﬂÇÈ
	while (rotZ > PI)
	{
		rotZ -= PI * 2.0f;
	}
	while (rotZ < -PI)
	{
		rotZ += PI * 2.0f;
	}

	// è∞
	if (fabsf(rotZ) < 0.1f)
	{
		m_Surface = ENEMY_SURFACE_FLOOR;
	}
	// ï«
	else if (fabsf(fabsf(rotZ) - HALF_PI) < 0.1f)
	{
		m_Surface = ENEMY_SURFACE_WALL;
	}
	// ìVà‰
	else if (fabsf(fabsf(rotZ) - PI) < 0.1f)
	{
		m_Surface = ENEMY_SURFACE_CEILING;
	}
}

bool EnemyBase::CheckHitStage(VECTOR nextPos)
{
	if (m_AABB == nullptr)
	{
		return false;
	}

	VECTOR prevPos = m_Pos;

	m_Pos = nextPos;

	const std::vector<StageObject*>& stageObjects = StageObjectManager::GetInstance()->GetStageObjects();

	bool isHit = false;

	for (auto obj : stageObjects)
	{
		if (obj == nullptr) continue;

		const CollisionAABB* objAABB = obj->GetAABB();

		if (objAABB == nullptr) continue;

		if (m_AABB->CheckAABB(objAABB))
		{
			isHit = true;
			break;
		}
	}

	// å≥ÇÃç¿ïWÇ…ñﬂÇ∑
	m_Pos = prevPos;

	return isHit;
}