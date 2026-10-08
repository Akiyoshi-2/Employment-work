#include "BigRoomba.h"
#include "../../Collision/CollisionAABB.h"
#include "../../StageObject/StageObjectManager.h"
#include "../../StageObject/StageObject.h"

#define MOVE_SPEED 0.5f

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

	m_Surface = ENEMY_SURFACE_FLOOR;
	m_Dir = ENEMY_DIR_LEFT;

	m_Move = VGet(-MOVE_SPEED, 0.0f, 0.0f);

	m_AABB = new CollisionAABB();

	m_AABB->SetTargetPos(&m_Pos);

	m_AABB->SetLocalPos(VGet(50.0f, 10.0f, 0.0f));
	m_AABB->SetSize(VGet(2.0f, 2.0f, 2.0f));
}

void BigRoomba::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/Machine/BigRoomba.x");
}

void BigRoomba::Start()
{

}

void BigRoomba::Step()
{
	
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

	clone->m_Handle = MV1DuplicateModel(m_Handle);

	// AABB‚Íclone‘¤‚ÅV‚µ‚­ì¬‚·‚é
	clone->m_AABB = nullptr;
	return clone;
}