#include "NormalItem.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Collision/CollisionAABB.h"

NormalItem::NormalItem()
{
}

NormalItem::~NormalItem()
{
}

void NormalItem::Init()
{
	
}

void NormalItem::Load()
{
	switch (m_ItemID)
	{
	case ITEM_HEAL:
		m_Handle = MV1LoadModel("Data/Item/未制作");
		break;

	case ITEM_SPEED_UP:
		m_Handle = MV1LoadModel("Data/Item/未制作");
		break;

	case ITEM_DAMAGE_UP:
		m_Handle = MV1LoadModel("Data/Item/未制作");
		break;

	case ITEM_INVINCIBLE:
		m_Handle = MV1LoadModel("Data/Item/未制作");
		break;
	}
}

void NormalItem::Start()
{
	
}

void NormalItem::Step()
{
	
}

NormalItem* NormalItem::Clone()
{
	NormalItem* clone = new NormalItem();

	clone->m_ItemID = m_ItemID;
	clone->m_Pos = m_Pos;
	clone->m_Rot = m_Rot;
	clone->m_Scale = m_Scale;

	clone->m_Handle = MV1DuplicateModel(m_Handle);

	return clone;
}

void NormalItem::PlayerGetItem()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr) return;

	switch (m_ItemID)
	{
	case ITEM_HEAL:
		// HP回復

		break;

	case ITEM_SPEED_UP:
		// 移動速度アップ

		break;

	case ITEM_DAMAGE_UP:
		// 射撃ダメージアップ

		break;

	case ITEM_INVINCIBLE:
		// 無敵状態

		break;
	
	}
}