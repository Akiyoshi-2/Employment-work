#include "BombEnemy.h"
#include "../../Collision/CollisionAABB.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerManager.h"
#include "../../StageObject/StageObject.h"
#include "../../StageObject/StageObjectManager.h"
#include "../../MyMath/MyMath.h"
#include <vector>

#define MOVE_SPEED 0.1f
#define SEARCH_RANGE 30.0f
#define EXPLOSION_RANGE 5.0f
#define EXPLOSION_DAMAGE 3

BombEnemy::BombEnemy()
{
	m_HP = 0;
	m_State = BOMB_STATE_WAIT;
	m_IsExploded = false;
	m_SearchRange = SEARCH_RANGE;
}

BombEnemy::~BombEnemy()
{
}

void BombEnemy::Init()
{
	m_HP = 20;

	m_State = BOMB_STATE_WAIT;
	m_IsExploded = false;

	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_AABB = new CollisionAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));
}

void BombEnemy::Load()
{

	m_Handle = MV1LoadModel("Data/Enemy/Machine/BombEnemy(Stay).x");
}

void BombEnemy::ChangeModel(const char* modelPath)
{
	// 現在のモデルを削除
	if (m_Handle != 0)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = 0;
	}

	// 新しいモデルを読み込む
	m_Handle = MV1LoadModel(modelPath);

	//現在の座標、回転スケールを反映
	if (m_Handle != -1 && m_Handle != 0)
	{
		MV1SetPosition(m_Handle, m_Pos);
		MV1SetRotationXYZ(m_Handle, m_Rot);
		MV1SetScale(m_Handle, m_Scale);
	}
}

void BombEnemy::Start()
{
	m_State = BOMB_STATE_WAIT;
	m_IsExploded = false;
	m_Move = VGet(0.0f, 0.0f, 0.0f);
}

void BombEnemy::Step()
{
	if (m_IsExploded || m_AABB == nullptr) { return; }

	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr) { return; }

	VECTOR playerPos = player->GetPos();

	// 待機状態
	if (m_State == BOMB_STATE_WAIT)
	{
		VECTOR diff = VSub(playerPos, m_Pos);

		if (VSize(diff) <= m_SearchRange)
		{
			m_State = BOMB_STATE_CHASE;
			// モデル変更
			ChangeModel("Data/Enemy/Machine/BombEnemy(Hunt).x");
		}
		else
		{
			m_Move = VGet(0.0f, 0.0f, 0.0f);
			return;
		}
	}

	// 攻撃状態
	if (m_State == BOMB_STATE_CHASE)
	{
		VECTOR diff = VSub(playerPos, m_Pos);
		float distance = VSize(diff);

		if (distance > 0.001f)
		{
			VECTOR direction = VScale(diff, 1.0f / distance);
			m_Move = VScale(direction, MOVE_SPEED);
		}
		else
		{
			m_Move = VGet(0.0f, 0.0f, 0.0f);
		}

		// 衝突判定
		VECTOR prevPos = m_Pos;
		VECTOR nextPos = VAdd(m_Pos, m_Move);

		m_Pos = nextPos;

		const std::vector<StageObject*>& stageObjects = StageObjectManager::GetInstance()->GetStageObjects();

		bool hitStage = false;

		for (auto obj : stageObjects)
		{
			if (obj == nullptr) continue;

			const CollisionAABB* objAABB = obj->GetAABB();

			if (objAABB == nullptr) continue;
			
			if (m_AABB->CheckAABB(objAABB))
			{
				hitStage = true;
				break;
			}
		}

		m_Pos = prevPos;

		if (hitStage)
		{
			Explode();
		}
	}
}

EnemyBase* BombEnemy::Clone()
{
	BombEnemy* clone = new BombEnemy();

	clone->m_HP = m_HP;

	clone->m_State = BOMB_STATE_WAIT;
	clone->m_IsExploded = false;
	clone->m_SearchRange = m_SearchRange;

	clone->m_Surface = m_Surface;
	clone->m_Dir = m_Dir;
	clone->m_Pos = m_Pos;
	clone->m_Rot = m_Rot;
	clone->m_Scale = m_Scale;
	clone->m_Move = VGet(0.0f, 0.0f, 0.0f);

	clone->m_Handle = MV1DuplicateModel(m_Handle);

	clone->m_AABB = nullptr;
	return clone;
}

void BombEnemy::OnHitPlayer()
{
	Explode();
}

void BombEnemy::Explode()
{
	if (m_IsExploded) return;
	

	m_IsExploded = true;
	m_State = BOMB_STATE_EXPLODED;
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	// 爆発範囲内のプレイヤーにダメージ
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player != nullptr)
	{
		VECTOR diff = VSub(player->GetPos(), m_Pos);

		if (VSize(diff) <= EXPLOSION_RANGE)
		{
			player->TakeDamage(EXPLOSION_DAMAGE);
		}
	}

	// 爆発エフェクトは後から追加する
}