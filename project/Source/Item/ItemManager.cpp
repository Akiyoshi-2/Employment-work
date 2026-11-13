#include "ItemManager.h"
#include "NormalItem.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Collision/CollisionAABB.h"

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
	// 回復アイテム
	m_OriginalItem[ITEM_HEAL] = new NormalItem();
	m_OriginalItem[ITEM_HEAL]->SetItemID(ITEM_HEAL);
	m_OriginalItem[ITEM_HEAL]->Init();

	// スピードアップアイテム
	m_OriginalItem[ITEM_SPEED_UP] = new NormalItem();
	m_OriginalItem[ITEM_SPEED_UP]->SetItemID(ITEM_SPEED_UP);
	m_OriginalItem[ITEM_SPEED_UP]->Init();

	// 攻撃アップアイテム
	m_OriginalItem[ITEM_DAMAGE_UP] = new NormalItem();
	m_OriginalItem[ITEM_DAMAGE_UP]->SetItemID(ITEM_DAMAGE_UP);
	m_OriginalItem[ITEM_DAMAGE_UP]->Init();

	// 無敵化アイテム
	m_OriginalItem[ITEM_INVINCIBLE] = new NormalItem();
	m_OriginalItem[ITEM_INVINCIBLE]->SetItemID(ITEM_INVINCIBLE);
	m_OriginalItem[ITEM_INVINCIBLE]->Init();
}

void ItemManager::Load()
{
	for (int i = 0; i < ITEM_MAX; i++)
	{
		if (m_OriginalItem[i] != nullptr)
		{
			m_OriginalItem[i]->Load();
		}
	}
}

void ItemManager::Start()
{

}

void ItemManager::Step()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr) return;

	// 更新処理
	for (auto item : m_ItemList)
	{
		item->Step();
	}

	// プレイヤーとアイテムの接触判定
	CheckHitPlayer(player->GetCollisionAABB());
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

void ItemManager::CheckHitPlayer(const CollisionAABB* playerAABB)
{
	if (playerAABB == nullptr) return;

	auto itr = m_ItemList.begin();

	while (itr != m_ItemList.end());
	{
		ItemBase* item = *itr;

		// プレイヤーとアイテムの当たり判定
		if (item->GetCollisionAABB()->CheckAABB(playerAABB))
		{
			// アイテム取得処理
			item->PlayerGetItem();

			// アイテム削除
			delete item;
			itr = m_ItemList.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}