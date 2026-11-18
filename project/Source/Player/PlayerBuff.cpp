#include "PlayerBuff.h"

PlayerBuff::PlayerBuff()
{
	m_MoveSpeed = BASE_MOVE_SPEED;
	m_SpeedUpTimer = 0.0f;

	m_AttackPower = BASE_ATTACK_POWER;
	m_DamageUpTimer = 0.0f;

	for (int i = 0; i < CURRENCY_MAX; i++)
	{
		m_CurrencyCount[i] = 0;
	}
}

PlayerBuff::~PlayerBuff()
{
}

void PlayerBuff::Update()
{
	// スピードアップアイテム
	if (m_SpeedUpTimer > 0.0f)
	{
		m_SpeedUpTimer -= 1.0f / 60.0f;

		if (m_SpeedUpTimer <= 0.0f)
		{
			m_SpeedUpTimer = 0.0f;
			m_MoveSpeed = BASE_MOVE_SPEED;
		}
	}

	// ダメージアップアイテム
	if (m_DamageUpTimer > 0.0f)
	{
		m_DamageUpTimer -= 1.0f / 60.0f;

		if (m_DamageUpTimer <= 0.0f)
		{
			m_DamageUpTimer = 0.0f;
			m_AttackPower = BASE_ATTACK_POWER;
		}
	}
}

void PlayerBuff::IncreaseMoveSpeed(float value, float duration)
{
	if (value <= 0.0f || duration <= 0.0f) return;

	m_MoveSpeed += value;
	m_SpeedUpTimer += duration;
}

void PlayerBuff::IncreaseAttackPower(int value, float duration)
{
	if (value <= 0.0f || duration <= 0.0f) return;

	m_AttackPower += value;
	m_DamageUpTimer = duration;
}

void PlayerBuff::AddCurrency(CURRENCY_ID id, int amount)
{
	if (id < 0 || id >= CURRENCY_MAX) return;
	if (amount <= 0) return;

	m_CurrencyCount[id] += amount;
}

bool PlayerBuff::UseCurrency(CURRENCY_ID id, int amount)
{
	if (id < 0 || id >= CURRENCY_MAX) return false;
	if (amount <= 0) return false;

	if (m_CurrencyCount[id] < amount)return false;

	m_CurrencyCount[id] -= amount;

	return true;
}

int PlayerBuff::GetCurrencyCount(CURRENCY_ID id) const
{
	if (id < 0 || id >= CURRENCY_MAX) return 0;

	return m_CurrencyCount[id];
}