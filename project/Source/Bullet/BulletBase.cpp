#include "BulletBase.h"

BulletBase::BulletBase()
{
    m_Handle = -1;

    m_Pos = VGet(0.0f, 0.0f, 0.0f);
    m_Move = VGet(0.0f, 0.0f, 0.0f);

    m_IsDead = false;
}

BulletBase::~BulletBase()
{
}

void BulletBase::Init()
{
}

void BulletBase::Load()
{
}

void BulletBase::Start()
{
}

void BulletBase::Step()
{
}

void BulletBase::Update()
{
    m_Pos = VAdd(m_Pos, m_Move);
}

void BulletBase::Draw()
{
    if (m_Handle != -1)
    {
        DrawGraph((int)m_Pos.x, (int)m_Pos.y, m_Handle, TRUE);
    }
}

void BulletBase::Fin()
{
}

void BulletBase::SetPos(float x, float y, float z)
{
    m_Pos = VGet(x, y, z);
}

void BulletBase::SetMove(float x, float y, float z)
{
    m_Move = VGet(x, y, z);
}

bool BulletBase::IsDead() const
{
    return m_IsDead;
}

void BulletBase::SetDead()
{
    m_IsDead = true;
}