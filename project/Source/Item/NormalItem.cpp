#include "NormalItem.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Collision/CollisionAABB.h"
#include "../MyMath/MyMath.h"

NormalItem::NormalItem()
{
}

NormalItem::~NormalItem()
{
}

void NormalItem::Init()
{
	m_AABB = new CollisionAABB();

	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetSize(VGet(4.0f, 4.0f, 4.0f));
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
}

void NormalItem::Load()
{
	switch (m_ItemID)
	{
	case ITEM_HEAL:
		m_Handle = MV1LoadModel("Data/Item/HealBox.x");
		break;

	case ITEM_SPEED_UP:
		m_Handle = MV1LoadModel("Data/Item/SpeedBox.x");
		break;

	case ITEM_DAMAGE_UP:
		m_Handle = MV1LoadModel("Data/Item/PowerBox.x");
		break;

	case ITEM_INVINCIBLE:
		m_Handle = MV1LoadModel("Data/Item/InvincibleBox.x");
		break;
	}
}

void NormalItem::Start()
{
	
}

void NormalItem::Step()
{
	if (!m_IsDrop) return;

	if (!m_IsGround)
	{

	}
}

NormalItem* NormalItem::Clone()
{
	NormalItem* clone = new NormalItem();

	clone->m_ItemID = m_ItemID;
	clone->m_Pos = m_Pos;
	clone->m_Rot = m_Rot;
	clone->m_Scale = m_Scale;

	clone->m_Handle = MV1DuplicateModel(m_Handle);
	clone->m_AABB = nullptr;

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
		Hear();
		break;

	case ITEM_SPEED_UP:
		// 移動速度アップ
		SpeedUp();
		break;

	case ITEM_DAMAGE_UP:
		// 射撃ダメージアップ
		DamageUp();
		break;

	case ITEM_INVINCIBLE:
		// 無敵状態
		Invincible();
		break;
	
	}
}

// HP回復アイテム
void NormalItem::Hear()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr) return;

	player->RecoverHP();
}

// スピードアップアイテム
void NormalItem::SpeedUp()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr) return;

	player->IncreaseMoveSpeed(0.2f, 20.0f);
}

// 攻撃力アップアイテム
void NormalItem::DamageUp()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr) return;

	player->IncreaseAttackPower(1, 30.0f);
}

// 無敵化アイテム
void NormalItem::Invincible()
{
	Player* player = PlayerManager::GetInstance()->GetPlayer();

	if (player == nullptr) return;

	player->Invincibility(20.0f);
}
