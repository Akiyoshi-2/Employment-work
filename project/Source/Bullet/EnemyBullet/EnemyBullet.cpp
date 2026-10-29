#include "EnemyBullet.h"


EnemyBullet::EnemyBullet()
{
}

EnemyBullet::~EnemyBullet()
{
	Fin();
}

void EnemyBullet::Init()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	m_IsDead = false;

	if (m_AABB != nullptr)
	{
		delete m_AABB;
		m_AABB = nullptr;
	}

	m_AABB = new CollisionAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(0.5f, 0.5f, 0.5f));
}

void EnemyBullet::Load()
{

}

void EnemyBullet::Start()
{

}

void EnemyBullet::Step()
{

}

void EnemyBullet::Update()
{
	BulletBase::Update();
}

void EnemyBullet::Draw()
{
	DrawSphere3D(m_Pos, 0.5f, 8, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
}

void EnemyBullet::SetDirection(VECTOR direction)
{
	m_Move = direction;
}

void EnemyBullet::SetPosition(VECTOR pos)
{
	m_Pos = pos;
}