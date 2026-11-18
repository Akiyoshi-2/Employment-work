#pragma once
#include "../Item/ItemParameter.h"

class PlayerBuff
{
public:
	PlayerBuff();
	~PlayerBuff();

	void Update();

	float GetMoveSpeed() const { return m_MoveSpeed; }
	int GetAttackPower() const { return m_AttackPower; }

	void IncreaseMoveSpeed(float value, float duration);
	void IncreaseAttackPower(int value, float duration);

	// デバッグ用効果時間表示
	float GetSpeedUpTimer() const { return m_SpeedUpTimer; }
	float GetDamageUpTimer() const { return m_DamageUpTimer; }

	// 通貨を追加
	void AddCurrency(CURRENCY_ID id, int amount);

	// 通貨を消費
	bool UseCurrency(CURRENCY_ID id, int amount);

	// 通貨の所持数を取得
	int GetCurrencyCount(CURRENCY_ID id) const;

private:
	static constexpr float BASE_MOVE_SPEED = 0.4f;
	static constexpr int BASE_ATTACK_POWER = 1;

	float m_MoveSpeed;
	float m_SpeedUpTimer;

	int m_AttackPower;
	float m_DamageUpTimer;

	int m_CurrencyCount[CURRENCY_MAX];
};

