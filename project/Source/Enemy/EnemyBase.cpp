#include "EnemyBase.h"
#include "../MyMath/MyMath.h"
#include "../Collision/CollisionAABB.h"
#include "../StageObject/StageObject.h"
#include "../StageObject/StageObjectManager.h"
#include <stdio.h>
#include <math.h>
#include <Windows.h>
#include <string>

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
	std::string message =
		"Scale: X=" + std::to_string(m_Scale.x) +
		" Y=" + std::to_string(m_Scale.y) +
		" Z=" + std::to_string(m_Scale.z) + "\n";

	OutputDebugStringA(message.c_str());

	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
	
}

void EnemyBase::Draw()
{
	MV1DrawModel(m_Handle);

	// 当たり判定描画
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

	// -180°～180°に収める
	while (rotZ > PI)
	{
		rotZ -= PI * 2.0f;
	}
	while (rotZ < -PI)
	{
		rotZ += PI * 2.0f;
	}

	// 床
	if (fabsf(rotZ) < 0.1f)
	{
		m_Surface = ENEMY_SURFACE_FLOOR;
	}
	// 壁
	else if (fabsf(fabsf(rotZ) - HALF_PI) < 0.1f)
	{
		m_Surface = ENEMY_SURFACE_WALL;
	}
	// 天井
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

	// 元の座標に戻す
	m_Pos = prevPos;

	return isHit;
}

bool EnemyBase::HasSurfaceAhead(VECTOR nextPos)
{
	if (m_AABB == nullptr) return false;

	const std::vector<StageObject*>& stageObjects = StageObjectManager::GetInstance()->GetStageObjects();

	// エネミーの当たり判定サイズを取得
	VECTOR size = m_AABB->GetSize();

	float width = size.x * 0.5f;
	float height = size.y * 0.5f;

	CollisionAABB probe;
	probe.SetTargetPos(&nextPos);
	probe.SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	switch (m_Surface)
	{
	case ENEMY_SURFACE_FLOOR:
		nextPos.y -= height + 0.1f;
		nextPos.x += (m_Move.x > 0.0f) ? width + 0.1f : -width - 0.1f;
		probe.SetSize(VGet(0.1f, 0.1f, size.z));
		break;

	case ENEMY_SURFACE_WALL:
		nextPos.y += (m_Move.y > 0.0f) ? height + 0.1f : -height - 0.1f;
		probe.SetSize(VGet(0.1f, 0.1f, size.z));
		break;

	case ENEMY_SURFACE_CEILING:
		nextPos.y += height + 0.1f;
		nextPos.x += (m_Move.x > 0.0f) ? width + 0.1f : -width - 0.1f;
		probe.SetSize(VGet(0.1f, 0.1f, size.z));
		break;

	default:
		return false;
	}

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

void EnemyBase::UpdateRot()
{
	const float HALF_PI = DX_PI_F * 0.5f;
	const float PI = DX_PI_F;

	switch (m_Surface)
	{
	case ENEMY_SURFACE_FLOOR:
		if (m_Dir == ENEMY_DIR_LEFT)
		{
			m_Rot.y = 0.0f;
		}
		else if (m_Dir == ENEMY_DIR_RIGHT)
		{
			m_Rot.y = PI;
		}
		break;

	case ENEMY_SURFACE_WALL:
		if (m_Dir == ENEMY_DIR_UP)
		{
			m_Rot.z = HALF_PI;
		}
		else if (m_Dir == ENEMY_DIR_DOWN)
		{
			m_Rot.z = -HALF_PI;
		}
		break;

	case ENEMY_SURFACE_CEILING:
		if (m_Dir == ENEMY_DIR_LEFT)
		{
			m_Rot.y = PI;
		}
		else if (m_Dir == ENEMY_DIR_RIGHT)
		{
			m_Rot.y = 0.0f;
		}
		break;
	
	default:
		break;
	}
}