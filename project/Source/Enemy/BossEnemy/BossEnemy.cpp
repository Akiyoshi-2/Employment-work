#include "BossEnemy.h"
#include "BossAttack.h"
#include "../../Collision/CollisionAABB.h"
#include "../../StageObject/StageObject.h"
#include "../../StageObject/StageObjectManager.h"
#include <math.h>

BossEnemy::BossEnemy()
{
	m_Mode = BOSS_MODE_NORMAL;
}

BossEnemy::~BossEnemy()
{

}

void BossEnemy::Init()
{
	m_HP = MAX_HP;

	m_Mode = BOSS_MODE_NORMAL;

	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_MoveDirX = 1.0f;

	m_FloatBaseY = m_Pos.y;
	m_FloatTimer = 0.0f;

	m_AABB = new CollisionAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));
}

void BossEnemy::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/BossEnemy/ñ¢äÆê¨");
}

void BossEnemy::Start()
{
	m_BossAttack.Init();
}

void BossEnemy::Step()
{
	// èÛë‘ïœçX
	if (m_Mode == BOSS_MODE_NORMAL && m_HP <= MAX_HP * RAGE_HP_RATE)
	{
		m_Mode = BOSS_ENEMY_RAGE;
	}

	float moveSpeed = MOVE_SPEED;

	if (m_Mode == BOSS_ENEMY_RAGE)
	{
		moveSpeed = RAGE_MOVE_SPEED;
	}

	// Xé≤ÇÃà⁄ìÆ
	float nextX = m_Pos.x + moveSpeed * m_MoveDirX;

	if (nextX >= m_MoveMaxX)
	{
		m_MoveDirX = -1.0f;
	}
	else if (nextX <= m_MoveMaxX)
	{
		m_MoveDirX = 1.0f;
	}

	m_Move.x = moveSpeed * m_MoveDirX;

	// Yé≤ÇÃà⁄ìÆ
	m_FloatTimer += 0.03;
	float targetY = m_FloatBaseY + sinf(m_FloatTimer * FLOAT_SPEED) * FLOAT_HEIGHT;

	m_Move.y = targetY - m_Pos.y;

	UpdateRot();

	m_BossAttack.Step();
}

void BossEnemy::OnHitPlayer()
{

}

void BossEnemy::SetMoveRange(float minX, float maxX)
{
	m_MoveMinX = minX;
	m_MoveMaxX = maxX;

}

//EnemyBase* BossEnemy::Clone()
//{
//
//}

