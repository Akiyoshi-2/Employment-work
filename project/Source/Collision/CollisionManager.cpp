#include "CollisionManager.h"
#include "CollisionAABB.h"
#include "CollisionSphere.h"
#include "../Player/PlayerManager.h"
#include "../Player/Player.h"

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

CollisionSphere* CollisionManager::CreateSphere()
{
	CollisionSphere* sphere = new CollisionSphere;
	m_Sphere.push_back(sphere);

	return sphere;
}
