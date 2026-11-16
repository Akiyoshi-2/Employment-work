#pragma once

class PlayerBuff
{
public:
	PlayerBuff();
	~PlayerBuff();

	void Update();

	// ステータス取得
	float GetMoveSpeed() const { return m_MoveSpeed; }
	int GetAttackPower() const { return m_AttackPower; }

	// ステータスを取得
	void IncreaseMoveSpeed(float value, float duration);
	void IncreaseAttackPower(int value, float duration);

private:
	static constexpr float BASE_MOVE_SPEED = 0.4f;
	static constexpr int BASE_ATTACK_POWER = 1;

	float m_MoveSpeed;
	float m_SpeedUpTimer;

	int m_AttackPower;
	float m_DamageUpTimer;
};

