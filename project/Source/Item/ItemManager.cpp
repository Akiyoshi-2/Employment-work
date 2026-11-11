#include "ItemManager.h"


ItemManager* ItemManager::m_Instance = nullptr;

ItemManager::ItemManager()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		m_OriginalItem[i] = nullptr;
	}
}

ItemManager::~ItemManager()
{

}

void ItemManager::Init()
{

}

void ItemManager::Load()
{

}

void ItemManager::Start()
{

}

void ItemManager::Step()
{

}

void ItemManager::Update()
{
	
}

void ItemManager::Draw()
{
	
}

void ItemManager::Fin()
{
	
}