#include "ShootingEnemy.h"
#include "../../Collision/CollisionAABB.h"
#include "../../StageObject/StageObject.h"
#include "../../StageObject/StageObjectManager.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerManager.h"
#include "../../MyMath/MyMath.h"
#include "../../Bullet/BulletManager.h"
#include "../../Bullet/EnemyBullet/EnemyBullet.h"
#include <vector>

#define MOVE_SPEED 0.3
#define MOVE_TRACK_SPEED 0.5

ShootingEnemy::ShootingEnemy()
{
}

ShootingEnemy::~ShootingEnemy()
{
}

void ShootingEnemy::Init()
{
	m_HP = 30;

	m_Surface = ENEMY_SURFACE_NONE;
	m_Dir = ENEMY_DIR_NONE;

	m_State = SHOOTING_NORMAL;
	m_TrackDirection = 1.0f;
	m_ShootTimer = 0.0f;

	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_AABB = new CollisionAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(6.0f, 6.0f, 6.0f));
}

void ShootingEnemy::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/Machine/ShootingEnemy.x");

}

void ShootingEnemy::Start()
{
	m_State = SHOOTING_NORMAL;
	m_TrackDirection = 1.0f;
	m_ShootTimer = 0.0f;

	m_Dir - ENEMY_DIR_RIGHT;
	m_Move = VGet(MOVE_SPEED, 0.0f, 0.0f);

	m_Scale = VGet(3.0f, 3.0f, 3.0f);

	UpdateRot();
}

void ShootingEnemy::Step()
{
	if (m_AABB == nullptr) return;

	Player* player = PlayerManager::GetInstance()->GetPlayer();
	if (player ==nullptr) return;

	VECTOR playerPos = player->GetPos();
	VECTOR diff = VSub(playerPos, m_Pos);
	float distance = VSize(diff);

	// 索敵状態を更新
	if (distance <= m_SearchRange)
	{
		m_State = SHOOTING_TRACK;
	}
	else
	{
		m_State = SHOOTING_NORMAL;
	}

	// 射撃タイマー
	if (m_ShootTimer > 0.0f)
	{
		m_ShootTimer -= 1.0f / 60.0f;

		if (m_ShootTimer < 0.0f)
		{
			m_ShootTimer = 0.0f;
		}
	}

	// 通常巡回
	if (m_State == SHOOTING_NORMAL)
	{
		m_Move = VGet(MOVE_SPEED * m_TrackDirection, 0.0f, 0.0f);

		VECTOR nextPos = VAdd(m_Pos, m_Move);

		bool hasSurface = HasSurfaceAhead(nextPos);
		bool hitStage = CheckHitStage(nextPos);

		if (!hasSurface || hitStage)
		{
			m_TrackDirection *= -1.0f;
			m_Dir = (m_TrackDirection > 0.0f) ? ENEMY_DIR_RIGHT : ENEMY_DIR_LEFT;
			m_Move = VGet(0.0f, 0.0f, 0.0f);
			
			UpdateRot();
			return;
		}

		m_Pos = nextPos;

		m_Dir = (m_TrackDirection > 0.0f) ? ENEMY_DIR_RIGHT : ENEMY_DIR_LEFT;

		UpdateRot();
		return;
	}
	// Player追跡
	else if (m_State == SHOOTING_TRACK)
	{
		// プレイヤーの方向を計算
		float diffX = playerPos.x - m_Pos.x;

		if (fabsf(diffX) > 0.001f)
		{
			m_TrackDirection = (diffX > 0.0f) ? 1.0f : -1.0f;
		}

		// 射程内なら射撃
		if (distance <= m_ShootRange && m_ShootTimer <= 0.0f)
		{
			Shoot(playerPos);
			m_ShootTimer = m_ShootInterval;
		}

		// プレイヤーの方向へ移動
		VECTOR nextPos = VAdd(m_Pos, VGet(MOVE_TRACK_SPEED * m_TrackDirection, 0.0f, 0.0f)
		);

		// 床があり、障害物にぶつからない場合だけ移動
		if (HasSurfaceAhead(nextPos) && !CheckHitStage(nextPos))
		{
			m_Pos = nextPos;
		}

		m_Dir = (m_TrackDirection > 0.0f) ? ENEMY_DIR_RIGHT : ENEMY_DIR_LEFT;

		UpdateRot();
	}
}

void ShootingEnemy::Shoot(VECTOR playerPos)
{
	BulletManager* bulletManager = BulletManager::GetInstance();
	if (bulletManager == nullptr) return;

	EnemyBullet* bullet = new EnemyBullet();

	bullet->Init();

	bullet->SetPosition(m_Pos);

	VECTOR direction = VSub(playerPos, m_Pos);
	float distance = VSize(direction);

	if (distance > 0.001f)
	{
		direction = VScale(direction, 1.0f / distance);
	}
	else
	{
		direction = VGet(1.0f, 0.0f, 0.0f);
	}

	const float BULLET_SPEED = 0.8f;

	direction = VScale(direction, BULLET_SPEED);
	bullet->SetDirection(direction);

	bulletManager->AddBullet(bullet);
}

EnemyBase* ShootingEnemy::Clone()
{
	ShootingEnemy* clone = new ShootingEnemy();

	clone->m_HP = m_HP;
	clone->m_Surface = m_Surface;
	clone->m_Dir = m_Dir;
	clone->m_Pos = m_Pos;
	clone->m_Rot = m_Rot;
	clone->m_Scale = m_Scale;
	clone->m_Move = m_Move;

	clone->m_Handle = MV1DuplicateModel(m_Handle);

	clone->m_AABB = nullptr;
	return clone;
}

void ShootingEnemy::OnHitPlayer()
{

}