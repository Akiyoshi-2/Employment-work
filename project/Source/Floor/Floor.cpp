#include "Floor.h"
#include "../Collision/CollisionAABB.h"

#define DEFAULT_POS VGet(0.0f, 0.0f, 0.0f)


CollisionAABB m_Collision;

CollisionAABB* GetCollision()
{
	return &m_Collision;
}

Floor::Floor()
{
	m_Handle = 0;
	m_Pos = VGet(0.0f, 0.0f, 0.0f);
}

Floor::~Floor()
{
	Fin();
}

void Floor::Init()
{
	m_Collision.SetTargetPos(&m_Pos);
	m_Collision.SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_Collision.SetSize(VGet(40.0f, 2.0f, 40.0f));
}

void Floor::Load()
{
	m_Handle = MV1LoadModel("Data/MapData/âº/Blender/âºè∞.x");

	MV1SetupCollInfo(m_Handle, -1);
}

void Floor::Start()
{
	m_Pos = DEFAULT_POS;
}

void Floor::Step()
{

}

void Floor::Update()
{
	MV1SetPosition(m_Handle, m_Pos);
}

void Floor::Draw()
{
	MV1DrawModel(m_Handle);

#ifdef _DEBUG
	m_Collision.Draw();
#endif
}

void Floor::Fin()
{
	MV1DeleteModel(m_Handle);
}