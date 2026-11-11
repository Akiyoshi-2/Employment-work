#pragma once
#include "DxLib.h"
#include "ItemBase.h"
#include "ItemParameter.h"
#include <list>

class CollisionAABB;

class ItemManager
{
public:
	ItemManager();
	~ItemManager();

	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	static void CreateInstance() { if (!m_Instance) m_Instance = new ItemManager; }
	static ItemManager* GetInstance() { return m_Instance; }
	static void DeleteInstance() { if (m_Instance) delete m_Instance; m_Instance = nullptr; }

	ItemBase* CreateItem(ITEM_ID id, ITEM_CREATE_TYPE createType);
	ItemBase* CreateItem(ITEM_ID id, ITEM_CREATE_TYPE createType, VECTOR pos, VECTOR rot, VECTOR scale);

	bool CheckHitPlayer(const CollisionAABB* playerAABB) const;

private:
	static ItemManager* m_Instance;

	ItemBase* m_OriginalItem[ITEM_MAX];

	std::list<ItemBase*> m_ItemList;
};

