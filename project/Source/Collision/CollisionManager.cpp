#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"
#include "../StageObject/Block/Block.h"
#include "../StageObject/StageObjectManager.h"

CollisionManager* CollisionManager::m_Instance = nullptr;

CollisionManager::CollisionManager()
{
	m_AABB = {};
	m_Sphere = {};
}

CollisionManager::~CollisionManager()
{
	Fin();
}

void CollisionManager::Draw()
{
	for (CollisionAABB* aabb : m_AABB)
	{
		if (aabb)
		{
			aabb->Draw();
		}
	}

	for (CollisionSphere* pshere : m_Sphere)
	{
		if (pshere)
		{
			pshere->Draw();
		}
	}
}

void CollisionManager::Fin()
{
	for (CollisionAABB* aabb : m_AABB)
	{
		if (aabb)
		{
			delete aabb;
		}
	}
	m_AABB.clear();

	for (CollisionSphere* sphere : m_Sphere)
	{
		if (sphere)
		{
			delete sphere;
		}
	}
	m_Sphere.clear();
}

CollisionAABB* CollisionManager::CreateAABB()
{
	CollisionAABB* aabb = new CollisionAABB;
	m_AABB.push_back(aabb);

	return aabb;
}

void CollisionManager::DeleteAABB(CollisionAABB* aabb)
{
	auto it = std::find(m_AABB.begin(), m_AABB.end(), aabb);
	if (it != m_AABB.end())
	{
		delete *it;
		m_AABB.erase(it);
	}
}

CollisionSphere* CollisionManager::CreateSphere()
{
	CollisionSphere* sphere = new CollisionSphere;
	m_Sphere.push_back(sphere);

	return sphere;
}

void CollisionManager::DeleteSphere(CollisionSphere* sphere)
{
	auto it = std::find(m_Sphere.begin(), m_Sphere.end(), sphere);
	if (it != m_Sphere.end())
	{
		delete *it;
		m_Sphere.erase(it);
	}
}

void CollisionManager::CheckCollision()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();
	auto stageObjects = StageObjectManager::GetInstance()->GetStageObjects();

	player->CheckHitStageObjects(stageObjects);
}