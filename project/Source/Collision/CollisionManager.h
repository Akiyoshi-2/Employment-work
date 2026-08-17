#pragma once
#include <vector>

class CollisionAABB;
class CollisionSphere;

class CollisionManager
{
public:
	CollisionManager();
	~CollisionManager();

	static void CreateInstance() { if (!m_Instance) m_Instance = new CollisionManager; }
	static CollisionManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	void Draw();
	void Fin();

	CollisionAABB* CreateAABB();
	CollisionSphere* CreateSphere();

private:
	static CollisionManager* m_Instance;

	std::vector<CollisionAABB*> m_AABB;
	std::vector<CollisionSphere*> m_Sphere;
	
};
