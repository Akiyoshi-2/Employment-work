#include "NormalItem.h"
#include "../Player/Player.h"
#include "../Player/PlayerManager.h"
#include "../Collision/CollisionAABB.h"
#include "../MyMath/MyMath.h"

NormalItem::NormalItem()
{
	m_GetItemNum = 1;
	m_MinDropNum = 1;
	m_MaxDropNum = 1;
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

	switch (m_ItemID)
	{
	case ITEM_DROP_HEAL:
		m_MinDropNum = 0;
		m_MaxDropNum = 3;
		break;
	case ITEM_DROP_GEAR:
		m_MinDropNum = 1;
		m_MaxDropNum = 4;
		break;
	}
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

	case ITEM_DROP_HEAL:
		m_Handle = MV1LoadModel("Data/Item/HearCapsule.x");
		break;

	case ITEM_DROP_GEAR:
		m_Handle = MV1LoadModel("Data/Item/Gear.x");
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
		m_Move.y -= ITEM_GRAVITY;

		VECTOR nextPos = MyMath::VecAdd(m_Pos, m_Move);

		if (CheckHitStage(nextPos))
		{
			m_Move.y = 0.0f;
			m_IsGround = true;
		}
		else
		{
			m_Pos = nextPos;
		}
	}
	else
	{
		m_Rot.y += ROTATION_SPEED;
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
	// 配置型アイテム
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
	
	// ドロップアイテム
	case ITEM_DROP_HEAL:
		Hear();
		break;

	case ITEM_DROP_GEAR:
		player->GetBuff().AddCurrency(CURRENCY_GEAR, m_GetItemNum);
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

void NormalItem::ItemDrop(VECTOR pos)
{
	ItemBase::ItemDrop(pos);

	m_GetItemNum = GetRand(m_MaxDropNum - m_MinDropNum) + m_MinDropNum;
}