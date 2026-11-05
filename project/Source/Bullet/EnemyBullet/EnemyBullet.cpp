#include "EnemyBullet.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerManager.h"
#include "../../Collision/CollisionAABB.h"
#include <cmath>


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

	m_AABB = new CollisionAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(0.5f, 0.5f, 0.5f));
}

void EnemyBullet::Load()
{
	m_Handle = MV1LoadModel("Data/Bullet/EnemyBullet1.x");
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

	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr || m_AABB == nullptr) return;

	CollisionAABB* playerAABB = player->GetCollisionAABB();

	if (playerAABB == nullptr) return;

	if (m_AABB->CheckAABB(playerAABB))
	{
		player->TakeDamage(1);
		SetDead();
	}
}

void EnemyBullet::Draw()
{
	if (m_Handle == -1) return;

	MV1SetPosition(m_Handle, m_Pos);
	MV1DrawModel(m_Handle);

	// “–‚½‚è”»’è•`‰æ
	if (m_AABB != nullptr)
	{
		m_AABB->Draw();
	}
}

void EnemyBullet::Fin()
{
	if (m_Handle != -1)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = -1;
	}
}

void EnemyBullet::SetDirection(VECTOR direction)
{
	m_Move = direction;
}

void EnemyBullet::SetPosition(VECTOR pos)
{
	m_Pos = pos;
}

