#include "BossEnemy.h"
#include "BossAttack.h"
#include "../../Collision/CollisionAABB.h"
#include "../../StageObject/StageObject.h"
#include "../../StageObject/StageObjectManager.h"

BossEnemy::BossEnemy()
{
	m_IsGround = false;
}

BossEnemy::~BossEnemy()
{

}

void BossEnemy::Init()
{
	m_HP = 200;
	m_Surface = ENEMY_SURFACE_NONE;
	m_Dir = ENEMY_DIR_NONE;

	m_Move = VGet(0.0f, 0.0f, 0.0f);

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

}

void BossEnemy::Step()
{

}

//EnemyBase* BossEnemy::Clone()
//{
//
//}

void BossEnemy::OnHitPlayer()
{

}