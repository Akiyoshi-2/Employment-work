#include "BigRoomba.h"
#include "../../Collision/CollisionAABB.h"
#include "../../StageObject/StageObjectManager.h"
#include "../../StageObject/StageObject.h"
#include "../../MyMath/MyMath.h"
#include <vector>

#define MOVE_SPEED 0.1f

BigRoomba::BigRoomba()
{
	m_HP = 0;
}

BigRoomba::~BigRoomba()
{
}

void BigRoomba::Init()
{
	m_HP = 20;

	m_Surface = ENEMY_SURFACE_NONE;
	m_Dir = ENEMY_DIR_NONE;

	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_AABB = new CollisionAABB();

	m_AABB->SetTargetPos(&m_Pos);

	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(2.0f, 2.0f, 2.0f));
}

void BigRoomba::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/Machine/BigRoomba.x");
}

void BigRoomba::Start()
{
	switch (m_Surface)
	{
	case ENEMY_SURFACE_FLOOR:
		m_Dir = ENEMY_DIR_LEFT;
		m_Move = VGet(-MOVE_SPEED, 0.0f, 0.0f);
		break;

	case ENEMY_SURFACE_WALL:
		m_Dir = ENEMY_DIR_UP;
		m_Move = VGet(0.0f, MOVE_SPEED, 0.0f);
		break;

	case ENEMY_SURFACE_CEILING:
		m_Dir = ENEMY_DIR_LEFT;
		m_Move = VGet(-MOVE_SPEED, 0.0f, 0.0f);
		break;

	default:
		m_Dir = ENEMY_DIR_NONE;
		m_Move = VGet(0.0f, 0.0f, 0.0f);
		break;
	}

	UpdateRot();
}



void BigRoomba::Step()
{
	if (m_AABB == nullptr) return;
	
	const std::vector<StageObject*>& stageObjects = StageObjectManager::GetInstance()->GetStageObjects();

	// 移動前の座標を保存
	VECTOR prevPos = m_Pos;

	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	bool isHit = false;

	// ステージとの当たり判定
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

	m_Pos = prevPos;

	if (!isHit)
	{
		return;
	}

	// 移動方向反転
	switch (m_Surface)
	{
	case ENEMY_SURFACE_FLOOR:
		m_Move.x *= -1.0f;

		if (m_Dir == ENEMY_DIR_RIGHT)
		{
			m_Dir = ENEMY_DIR_LEFT;
		}
		else
		{
			m_Dir = ENEMY_DIR_RIGHT;
		}
		break;

	case ENEMY_SURFACE_WALL:
		m_Move.y *= 1.0f;

		if (m_Dir == ENEMY_DIR_UP)
		{
			m_Dir = ENEMY_DIR_DOWN;
		}
		else
		{
			m_Dir = ENEMY_DIR_UP;
		}
		break;

	case ENEMY_SURFACE_CEILING:
		m_Move.x *= 1.0f;

		if (m_Dir == ENEMY_DIR_LEFT)
		{
			m_Dir = ENEMY_DIR_RIGHT;
		}
		else
		{
			m_Dir = ENEMY_DIR_LEFT;
		}
		break;

	default:
		break;
	}

	UpdateRot();
}

EnemyBase* BigRoomba::Clone()
{
	BigRoomba* clone = new BigRoomba();

	clone->m_HP = m_HP;
	clone->m_Surface = m_Surface;
	clone->m_Dir = m_Dir;
	clone->m_Pos = m_Pos;
	clone->m_Rot = m_Rot;
	clone->m_Scale = m_Scale;
	clone->m_Move = m_Move;
	// *clone = *this;

	clone->m_Handle = MV1DuplicateModel(m_Handle);

	// AABBはclone側で新しく作成する
	clone->m_AABB = nullptr;
	return clone;
}

void BigRoomba::UpdateRot()
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
			m_Rot.z = PI;
		}
		else if (m_Dir == ENEMY_DIR_RIGHT)
		{
			m_Rot.z = 0.0f;
		}
		break;

	default:
		break;
	}
}

