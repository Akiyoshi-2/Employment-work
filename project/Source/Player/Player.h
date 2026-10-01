#pragma once
#include "DxLib.h"
#include "../Bullet/BulletManager.h"
#include "../Animation/Animation.h"
#include "../Collision/CollisionAABB.h"
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

	void CheckHitStageObjects(const std::vector<StageObject*>& stageObjects);

public:
	CollisionAABB* GetCollision() { return m_AABB; }

private:
	int m_HP;
	VECTOR m_Pos;
	VECTOR m_Move;
	VECTOR m_PrevPos;
	float m_Size;
	bool m_isTurn;
	bool m_IsGround;

	PlayerGravityDir m_GravityDir;

	float m_BulletCoolTime;
	float m_BulletInterval;

	AnimationData m_Animation[static_cast<std::size_t>(Player::PlayerAnimationType::MAX)];
	PlayerAnimationType m_NowAnim;

	BulletManager* m_BulletManager;

	CollisionAABB* m_AABB;
	//CollisionSphere m_Sphere;
};

