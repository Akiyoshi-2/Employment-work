#include "DxLib.h"
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

#define MOVE_SPEED 0.1
#define MOVE_TRACK_SPEED 0.15

ShootingEnemy::ShootingEnemy()
{
	m_BulletManager = nullptr;
	m_SearchRange = 0.0f;
	m_ShootInterval = 0.0f;
	m_ShootTimer = 0.0f;
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

	m_BulletManager = BulletManager::GetInstance();
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
	m_SearchRange = 50.0f;
	m_ShootInterval = 1.0f;

	m_Dir = ENEMY_DIR_RIGHT;
	m_Move = VGet(MOVE_SPEED, 0.0f, 0.0f);

	m_Scale = VGet(3.0f, 3.0f, 3.0f);

	m_Rot.y = 0.0f;
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

		bool hasSurface = CheckShootingEnemyFloor(nextPos);
		bool hitStage = CheckHitStage(nextPos);

		if (!hasSurface || hitStage)
		{
			m_TrackDirection *= -1.0f;
			m_Dir = (m_TrackDirection > 0.0f) ? ENEMY_DIR_RIGHT : ENEMY_DIR_LEFT;
			m_Move = VGet(0.0f, 0.0f, 0.0f);
						
			m_Rot.y = (m_TrackDirection > 0.0f) ? 0.0f : DX_PI_F;
			return;
		}

		m_Pos = nextPos;

		m_Dir = (m_TrackDirection > 0.0f) ? ENEMY_DIR_RIGHT : ENEMY_DIR_LEFT;

		m_Rot.y = (m_TrackDirection > 0.0f) ? 0.0f : DX_PI_F;
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
		if (m_ShootTimer <= 0.0f)
		{
			Shoot(playerPos);
			m_ShootTimer = m_ShootInterval;
		}

		m_Move = VGet(MOVE_TRACK_SPEED * m_TrackDirection, 0.0f, 0.0f);

		VECTOR nextPos = VAdd(m_Pos, m_Move);

		bool hasSurface = CheckShootingEnemyFloor(nextPos);
		bool hitStage = CheckHitStage(nextPos);

		// 床があり、障害物にぶつからない場合だけ移動
		if (hasSurface && !hitStage)
		{
			m_Pos = nextPos;
		}
		else
		{
			m_Move = VGet(0.0f, 0.0f, 0.0f);
		}

		m_Dir = (m_TrackDirection > 0.0f) ? ENEMY_DIR_RIGHT : ENEMY_DIR_LEFT;

		m_Rot.y = (m_TrackDirection > 0.0f) ? 0.0f : DX_PI_F;
	}
}

bool ShootingEnemy::CheckShootingEnemyFloor(VECTOR nextPos)
{
	if (m_AABB == nullptr) return false;

	const std::vector<StageObject*>& stageObjects = StageObjectManager::GetInstance()->GetStageObjects();

	// エネミーのAABBサイズ
	VECTOR size = m_AABB->GetSize();

	float halfWidth = size.x * 0.5f;
	float halfHeight = size.y * 0.5f;

	// 床の検出位置
	nextPos.x += (m_Move.x > 0.0f) ? halfWidth : -halfWidth;
	nextPos.y -= halfHeight;

	CollisionAABB probe;
	probe.SetTargetPos(&nextPos);
	probe.SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	probe.SetSize(VGet(size.x, size.y, size.z));

	// ステージとの衝突判定
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

void ShootingEnemy::Shoot(VECTOR playerPos)
{
	if (m_BulletManager == nullptr) return;

	EnemyBullet* bullet = new EnemyBullet();

	bullet->Init();
	bullet->Load();

	// プレイヤーの方向を計算
	VECTOR direction = VSub(playerPos, m_Pos);

	float distance = VSize(direction);

	if (distance > 0.001f)
	{
		direction = VScale(direction, 1.0f / distance); 
	}
	else
	{
		direction = VGet(0.0f, 0.0f, 1.0f); 
	}

	// 弾速
	const float BULLET_SPEED = 0.4f;

	// エネミーの前方方向を計算
	VECTOR forward = VGet(sinf(m_Rot.y), 0.0f, cosf(m_Rot.y));

	// エネミーの右方向を計算
	VECTOR right = VGet(cosf(m_Rot.y), 0.0f, -sinf(m_Rot.y));

	// 発射位置を設定
	bullet->SetPos(m_Pos.x + right.x * 3.0f, m_Pos.y, m_Pos.z + forward.z * 2.0f);
	// 移動量を設定
	bullet->SetMove(direction.x * BULLET_SPEED, direction.y * BULLET_SPEED, direction.z * BULLET_SPEED);

	m_BulletManager->AddBullet(bullet);
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
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr) return;

	player->TakeDamage(1);
}