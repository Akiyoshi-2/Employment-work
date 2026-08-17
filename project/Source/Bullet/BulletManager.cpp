#include "BulletManager.h"
#include "BulletBase.h"

BulletManager* BulletManager::m_Instance = nullptr;

BulletManager::BulletManager()
{
}

BulletManager::~BulletManager()
{
    Fin();
}

void BulletManager::Init()
{
}

void BulletManager::Load()
{
}

void BulletManager::Start()
{
}

void BulletManager::Step()
{
}

void BulletManager::Update()
{
    for (auto itr = m_BulletList.begin(); itr != m_BulletList.end();)
    {
        (*itr)->Update();

        if ((*itr)->IsDead())
        {
            delete* itr;
            itr = m_BulletList.erase(itr);
        }
        else
        {
            ++itr;
        }
    }
}

void BulletManager::Draw()
{
    for (auto bullet : m_BulletList)
    {
        bullet->Draw();
    }
}

void BulletManager::Fin()
{
    for (auto bullet : m_BulletList)
    {
        delete bullet;
    }

    m_BulletList.clear();
}

void BulletManager::AddBullet(BulletBase* bullet)
{
    m_BulletList.push_back(bullet);
}