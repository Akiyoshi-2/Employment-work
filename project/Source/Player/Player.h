#pragma once
#include "DxLib.h"
#include "../Bullet/BulletManager.h"
#include "../Animation/Animation.h"
#include "../Collision/CollisionAABB.h"

class Floor;

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

	void SetFloor(Floor* floor);

public:
	CollisionAABB* GetCollision()
	{
		return &m_Collision;
	}

private:
	int m_HP;
	VECTOR m_Pos;
	VECTOR m_Move;
	float m_Size;
	bool m_isTurn;
	bool m_IsGround;

	PlayerGravityDir m_GravityDir;

	float m_BulletCoolTime;
	float m_BulletInterval;

	AnimationData m_Animation[static_cast<std::size_t>(Player::PlayerAnimationType::MAX)];
	PlayerAnimationType m_NowAnim;

	BulletManager* m_BulletManager;

	Floor* m_Floor;

	CollisionAABB m_Collision;
};

