#pragma once
#include "DxLib.h"
#include "../Bullet/BulletManager.h"
#include "../Animation/Animation.h"
#include "../Collision/CollisionAABB.h"
#include "PlayerBuff.h"
#include <vector>

class CollisionSphere;
class StageObject;

class Player
{
public:
	Player();
	~Player();

	enum class PlayerGravityDir
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
	};

	enum class PlayerAnimationType
	{
		IDLE,
		RUN,
		JUMP,
		FALL,
		MAX,
		NONE = -1
	};

public:

	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	void ChangeAnimation(PlayerAnimationType anim);

	void SetBulletManager(BulletManager* manager);

	VECTOR GetPos() const { return m_Pos; }
	CollisionAABB* GetCollisionAABB() { return m_AABB; }
	// CollisionSphere* GetCollisionSphere() { return &m_Sphere; }

	// void SetTransform(VECTOR pos, VECTOR move, float size, bool isTurn, bool isGround, PlayerGravityDir gravityDir);

	void TakeDamage(int damage);
	int GetHP() const { return m_HP; }
	bool IsDefaeted() const { return m_HP <= 0; }

	void CheckHitStageObjects(const std::vector<StageObject*>& stageObjects);

	void SetGravityDir(PlayerGravityDir dir);
	PlayerGravityDir GetGravityDir() const { return m_GravityDir; }

	CollisionAABB* GetCollision() { return m_AABB; }

	void IncreaseMoveSpeed(float value, float duration);
	
	void IncreaseAttackPower(int value, float duration = 30.0f);
	
	void RecoverHP();
	
	void Invincibility(float duration);

	PlayerBuff& GetBuff() { return m_Buff; }

private:
	int m_HP;
	VECTOR m_Pos;
	VECTOR m_Move;
	VECTOR m_PrevPos;
	float m_Size;

	float m_BulletCoolTime;
	float m_BulletInterval;

	// 被ダメ時の無敵時間
	float m_InvincibleTimer;
	// アイテムによる無敵時間
	float m_ItemInvincibleTimer;

	bool m_isTurn;
	bool m_IsGround;
	bool m_IsVisible;
	static constexpr float INVINCIBLE_TIME = 1.0f;

	PlayerGravityDir m_GravityDir;
	
	BulletManager* m_BulletManager;

	AnimationData m_Animation[static_cast<std::size_t>(Player::PlayerAnimationType::MAX)];
	PlayerAnimationType m_NowAnim;

	CollisionAABB* m_AABB;
	//CollisionSphere m_Sphere;

	PlayerBuff m_Buff;
};

