#include "BigRoomba.h"
#include "../../Collision/CollisionAABB.h"
#include "../../StageObject/StageObjectManager.h"
#include "../../StageObject/StageObject.h"
#include "../../MyMath/MyMath.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerManager.h"
#include <vector>

#define MOVE_SPEED 0.1f

BigRoomba::BigRoomba()
{
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
	m_AABB->SetSize(VGet(5.0f, 2.0f, 4.0f));
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

	// 移動先を計算
	VECTOR nextPos = MyMath::VecAdd(m_Pos, m_Move);

	// 移動先に床・壁・天井があるか調べる
	bool hasSurface = HasSurfaceAhead(nextPos);

	// EnemyBaseの共通関数でステージとの衝突を判定
	bool isHit = CheckHitStage(nextPos);

	// ステージに衝突せず、進行方向に表面がある場合は移動
	if (!isHit && hasSurface)
	{
		m_Pos = nextPos;
		return;
	}

	// 移動方向を反転
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
		m_Move.y *= -1.0f;

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
		m_Move.x *= -1.0f;

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

	// 向きを更新
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

	printf("ShootingEnemy Scale: %f, %f, %f\n",
		clone->m_Scale.x,
		clone->m_Scale.y,
		clone->m_Scale.z);
}

void BigRoomba::OnHitPlayer()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr) return;

	player->TakeDamage(1);
}

