#include "BombEnemy.h"
#include "../../Collision/CollisionAABB.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerManager.h"
#include "../../StageObject/StageObject.h"
#include "../../StageObject/StageObjectManager.h"
#include "../../MyMath/MyMath.h"
#include <vector>

#define MOVE_SPEED 0.8f

BombEnemy::BombEnemy()
{
	m_HP = 0;
}

BombEnemy::~BombEnemy()
{
}

void BombEnemy::Init()
{
	m_HP = 20;

	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_AABB = new CollisionAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));
}

void BombEnemy::Load()
{

}

void BombEnemy::Start()
{

}

void BombEnemy::Step()
{

}

EnemyBase* BombEnemy::Clone()
{

}

void BombEnemy::OnHitPlayer()
{

}