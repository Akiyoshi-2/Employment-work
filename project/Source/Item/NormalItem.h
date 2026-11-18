#pragma once
#include "ItemBase.h"
#include "ItemParameter.h"

class NormalItem : public ItemBase
{
public:
	NormalItem();
	virtual~NormalItem();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;

	NormalItem* Clone() override;

	void PlayerGetItem() override;

	void ItemDrop(VECTOR pos) override;

private:
	void Hear();
	void SpeedUp();
	void DamageUp();
	void Invincible();

	int m_GetItemNum;

	int m_MinDropNum;
	int m_MaxDropNum;
};

