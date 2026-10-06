#include "BigRoomba.h"

#define MOVE_SPEED 0.5f

BigRoomba::BigRoomba()
{
	m_HP = 20;
	m_IsGround = false;
	m_IsWall = false;
	m_IsTurn = false;
}

BigRoomba::~BigRoomba()
{
}

void BigRoomba::Init()
{
}

void BigRoomba::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/‹@ŠB˜f¯/BigRoomba.x");
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
	*clone = *this;
	clone->m_Handle = MV1DuplicateModel(m_Handle);
	return clone;
}