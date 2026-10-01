#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Bullet/PlayerBullet/PlayerBullet.h"
#include "../Collision/CollisionManager.h"
#include "../Collision/CollisionAABB.h"
#include "../Collision/CollisionSphere.h"
#include "../StageObject/StageObject.h"
#include "../StageObject/StageObjectManager.h"
#include "../MyMath/MyMath.h"


#define MOVE_SPEED		0.4f
#define JUMP_POWER		2.0f
#define BULLET_SPEED	5.0f
#define GRAVITY			0.1f

struct PlayerAnimParam
{
	int interval;
	int frameNum;
	int width;
	int height;
};

Player::Player()
{
	m_HP = 10;		// HP
	m_Size = 5.0f;	// プレイヤーサイズ

	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_PrevPos = VGet(0.0f, 0.0f, 0.0f);
	
	m_isTurn = false;

	m_IsGround = false;

	m_NowAnim = PlayerAnimationType::IDLE;

	m_BulletManager = nullptr;

	m_BulletCoolTime = 0.0f;
	m_BulletInterval = 7.0f;

	m_GravityDir = PlayerGravityDir::DOWN;

	m_AABB = nullptr;
}

Player::~Player()
{
}

void Player::Init()
{

}

void Player::Load()
{
	
	// IDLE
	LoadDivGraph(
		TEXT("Data/Player/Player_Idle.png"),
		1,
		1,
		1,
		256,
		256,
		m_Animation[static_cast<int>(PlayerAnimationType::IDLE)].handle);

	StartAnimation(
		&m_Animation[static_cast<int>(PlayerAnimationType::IDLE)],
		9999,
		1,
		true);

	// RUN
	LoadDivGraph(
		TEXT("Data/Player/Player_Run2.png"),
		5,
		5,
		1,
		256,
		256,
		m_Animation[static_cast<int>(PlayerAnimationType::RUN)].handle);

	StartAnimation(
		&m_Animation[static_cast<int>(PlayerAnimationType::RUN)],
		7,
		5,
		true);

	// JUMP
	LoadDivGraph(
		TEXT("Data/Player/Player_Jump.png"),
		1,
		1,
		1,
		256,
		256,
		m_Animation[static_cast<int>(PlayerAnimationType::JUMP)].handle);

	StartAnimation(
		&m_Animation[static_cast<int>(PlayerAnimationType::JUMP)],
		9999,
		1,
		true);
}

void Player::Start()
{
	// 移動量を初期化
	m_Move = VGet(0.0, 0.0f, 0.0f);

	// AABBの当たり判定を設定
	m_AABB = CollisionManager::GetInstance()->CreateAABB();
	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(5.0f, 5.0f, 5.0f));

	
	m_Pos = VGet(10.0f, 10.0f, 0.0f);
}

void Player::Step()
{
	if (m_GravityDir == PlayerGravityDir::DOWN)
	{
		// 移動量リセット
		m_Move = VGet(0.0f, m_Move.y, 0.0f);
		// 重力
		m_Move.y -= GRAVITY;

		if (Input::IsInputKey(Input::KEY_RIGHT))
		{
			m_Move.x += MOVE_SPEED;
			m_isTurn = false;
		}

		if (Input::IsInputKey(Input::KEY_LEFT))
		{
			m_Move.x -= MOVE_SPEED;
			m_isTurn = true;
		}

		/*if (Input::IsInputKey(Input::KEY_UP))
		{
			m_Move.z += MOVE_SPEED;
		}

		if (Input::IsInputKey(Input::KEY_DOWN))
		{
			m_Move.z -= MOVE_SPEED;
		}*/

		if (Input::IsTriggerKey(Input::KEY_SPACE) && m_IsGround)
		{
			m_Move.y = JUMP_POWER;
			m_IsGround = false;
		}

		// 弾発射間隔
		if (m_BulletCoolTime > 0.0f)
		{
			m_BulletCoolTime--;
		}

		if (Input::IsInputKey(Input::KEY_Z))
		{
			if (m_BulletCoolTime <= 0.0f)
			{
				PlayerBullet* bullet = new PlayerBullet();

				bullet->Load();

				if (m_isTurn)
				{
					// 左向き
					bullet->SetPos(m_Pos.x - 1.0f, m_Pos.y, m_Pos.z);
					bullet->SetMove(-BULLET_SPEED, 0.0f, 0.0f);
				}
				else
				{
					// 右向き
					bullet->SetPos(m_Pos.x + 1.0f, m_Pos.y, m_Pos.z);
					bullet->SetMove(BULLET_SPEED, 0.0f, 0.0f);
				}

				m_BulletManager->AddBullet(bullet);

				m_BulletCoolTime = m_BulletInterval;
			}

		}
	}
	// 重力↑
	else if (m_GravityDir == PlayerGravityDir::UP)
	{
		// 移動量リセット
		m_Move = VGet(0.0f, m_Move.y, 0.0f);
		// 重力
		m_Move.y += GRAVITY;

		if (Input::IsInputKey(Input::KEY_RIGHT))
		{
			m_Move.x += MOVE_SPEED;
			m_isTurn = false;
		}

		if (Input::IsInputKey(Input::KEY_LEFT))
		{
			m_Move.x -= MOVE_SPEED;
			m_isTurn = true;
		}

		/*if (Input::IsInputKey(Input::KEY_UP))
		{
			m_Move.z += MOVE_SPEED;
		}

		if (Input::IsInputKey(Input::KEY_DOWN))
		{
			m_Move.z -= MOVE_SPEED;
		}*/

		if (Input::IsTriggerKey(Input::KEY_SPACE) && m_IsGround)
		{
			m_Move.y = -JUMP_POWER;
			m_IsGround = false;
		}

		// 弾発射間隔
		if (m_BulletCoolTime > 0.0f)
		{
			m_BulletCoolTime--;
		}

		if (Input::IsInputKey(Input::KEY_Z))
		{
			if (m_BulletCoolTime <= 0.0f)
			{
				PlayerBullet* bullet = new PlayerBullet();

				bullet->Load();

				if (m_isTurn)
				{
					// 左向き
					bullet->SetPos(m_Pos.x - 1.0f, m_Pos.y, m_Pos.z);
					bullet->SetMove(-BULLET_SPEED, 0.0f, 0.0f);
				}
				else
				{
					// 右向き
					bullet->SetPos(m_Pos.x + 1.0f, m_Pos.y, m_Pos.z);
					bullet->SetMove(BULLET_SPEED, 0.0f, 0.0f);
				}

				m_BulletManager->AddBullet(bullet);

				m_BulletCoolTime = m_BulletInterval;
			}

		}
	}
	// 重力←
	else if (m_GravityDir == PlayerGravityDir::LEFT)
	{
		// X方向の移動量を維持してY方向をリセット
		m_Move = VGet(m_Move.x, 0.0f, 0.0f);

		m_Move.x -= GRAVITY;

		// Y方向に移動
		if (Input::IsInputKey(Input::KEY_UP))
		{
			m_Move.y += MOVE_SPEED;
			m_isTurn = true;
		}
		if (Input::IsInputKey(Input::KEY_DOWN))
		{
			m_Move.y -= MOVE_SPEED;
			m_isTurn = false;
		}

		// ジャンプ
		if (Input::IsTriggerKey(Input::KEY_SPACE) && m_IsGround)
		{
			// 左向き重力なので、ジャンプは右方向
			m_Move.x = JUMP_POWER;
			m_IsGround = false;
		}

		// 弾発射間隔
		if (m_BulletCoolTime > 0.0f)
		{
			m_BulletCoolTime--;
		}

		// 弾発射
		if (Input::IsInputKey(Input::KEY_Z))
		{
			if (m_BulletCoolTime <= 0.0f)
			{
				PlayerBullet* bullet = new PlayerBullet();
				bullet->Load();
				if (m_isTurn)
				{
					bullet->SetPos(
						m_Pos.x - 1.0f,
						m_Pos.y,
						m_Pos.z);
					bullet->SetMove(
						-BULLET_SPEED,
						0.0f,
						0.0f);
				}
				else
				{
					bullet->SetPos(
						m_Pos.x + 1.0f,
						m_Pos.y,
						m_Pos.z);
					bullet->SetMove(
						BULLET_SPEED,
						0.0f,
						0.0f);
				}
				m_BulletManager->AddBullet(bullet);
				m_BulletCoolTime = m_BulletInterval;
			}
		}

	}
	// 重力→
	else if (m_GravityDir == PlayerGravityDir::RIGHT)
	{
		// X方向の移動量を維持してY方向をリセット
		m_Move = VGet(m_Move.x, 0.0f, 0.0f);

		m_Move.x += GRAVITY;

		// Y方向に移動
		if (Input::IsInputKey(Input::KEY_UP))
		{
			m_Move.y += MOVE_SPEED;
			m_isTurn = false;
		}
		if (Input::IsInputKey(Input::KEY_DOWN))
		{
			m_Move.y -= MOVE_SPEED;
			m_isTurn = true;
		}

		// ジャンプ
		if (Input::IsTriggerKey(Input::KEY_SPACE) && m_IsGround)
		{
			// 右向き重力なので、ジャンプは左方向
			m_Move.x = -JUMP_POWER;

			m_IsGround = false;
		}

		// 弾発射間隔
		if (m_BulletCoolTime > 0.0f)
		{
			m_BulletCoolTime--;
		}

		// 弾発射
		if (Input::IsInputKey(Input::KEY_Z))
		{
			if (m_BulletCoolTime <= 0.0f)
			{
				PlayerBullet* bullet = new PlayerBullet();

				bullet->Load();

				if (m_isTurn)
				{
					bullet->SetPos(
						m_Pos.x - 1.0f,
						m_Pos.y,
						m_Pos.z);

					bullet->SetMove(
						-BULLET_SPEED,
						0.0f,
						0.0f);
				}
				else
				{
					bullet->SetPos(
						m_Pos.x + 1.0f,
						m_Pos.y,
						m_Pos.z);

					bullet->SetMove(
						BULLET_SPEED,
						0.0f,
						0.0f);
				}

				m_BulletManager->AddBullet(bullet);

				m_BulletCoolTime = m_BulletInterval;
			}
		}
	}

	// 前回の座標を記録
	m_PrevPos = m_Pos;

	// 移動量を反映
	m_Pos = MyMath::VecAdd(m_Pos, m_Move);

	// アニメーション切り替え
	if (m_GravityDir == PlayerGravityDir::UP || 
		m_GravityDir == PlayerGravityDir::DOWN)
	{
		if (!m_IsGround && m_Move.y != 0.0f)
		{
			ChangeAnimation(PlayerAnimationType::JUMP);
		}
		else if (m_IsGround && m_Move.x != 0.0f)
		{
			ChangeAnimation(PlayerAnimationType::RUN);
		}
		else
		{
			ChangeAnimation(PlayerAnimationType::IDLE);
		}
	}
	else if (m_GravityDir == PlayerGravityDir::LEFT ||
		m_GravityDir == PlayerGravityDir::RIGHT)
	{
		if (!m_IsGround && m_Move.x != 0.0f)
		{
			ChangeAnimation(PlayerAnimationType::JUMP);
		}
		else if (m_IsGround && m_Move.y != 0.0f)
		{
			ChangeAnimation(PlayerAnimationType::RUN);
		}
		else
		{
			ChangeAnimation(PlayerAnimationType::IDLE);
		}
	}

	// アニメーション
	UpdateAnimation(&m_Animation[static_cast<int>(m_NowAnim)]);
}

void Player::Update()
{
	// 重力方向変更
	// 上方向
	if (Input::IsTriggerKey(Input::KEY_W))
	{
		m_GravityDir = PlayerGravityDir::UP;

		// 移動量をリセット
		m_Move.x = 0.0f;
		m_Move.y = 0.0f;

		// 接地状態解除
		m_IsGround = false;
	}
	// 下方向
	if (Input::IsTriggerKey(Input::KEY_S))
	{
		m_GravityDir = PlayerGravityDir::DOWN;

		// 移動量をリセット
		m_Move.x = 0.0f;
		m_Move.y = 0.0f;

		// 接地状態解除
		m_IsGround = false;
	}
	// 左方向
	if (Input::IsTriggerKey(Input::KEY_A))
	{
		m_GravityDir = PlayerGravityDir::LEFT;

		// 移動量をリセット
		m_Move.x = 0.0f;
		m_Move.y = 0.0f;

		// 接地状態解除
		m_IsGround = false;
	}
	// 右方向
	if (Input::IsTriggerKey(Input::KEY_D))
	{
		m_GravityDir = PlayerGravityDir::RIGHT;

		// 移動量をリセット
		m_Move.x = 0.0f;
		m_Move.y = 0.0f;

		// 接地状態解除
		m_IsGround = false;
	}


	// 重力↓
	if (m_GravityDir == PlayerGravityDir::DOWN)
	{
		
	}
	// 重力↑
	else if (m_GravityDir == PlayerGravityDir::UP)
	{
		
	}
	else if (m_GravityDir == PlayerGravityDir::LEFT)
	{

	}
	else if (m_GravityDir == PlayerGravityDir::RIGHT)
	{

	}

	
}

void Player::Draw()
{		
	AnimationData* anim = &m_Animation[static_cast<int>(m_NowAnim)];

	// 重力方向↓
	if (m_GravityDir == PlayerGravityDir::DOWN)
	{
		// 2D画像を3D空間に描画する
		DrawBillboard3D(
			m_Pos,
			0.5f,          // 画像中央(X)
			0.5f,          // 画像中央(Y)
			m_Size,        // サイズ
			0.0f,          // 回転
			GetAnimationHandle(anim),
			TRUE,
			m_isTurn,      // 左右反転
			FALSE          // 上下反転
		);
	}
	else if (m_GravityDir == PlayerGravityDir::UP)
	{
		DrawBillboard3D(
			m_Pos,
			0.5f,          
			0.5f,          
			m_Size,        
			0.0f,          
			GetAnimationHandle(anim),
			TRUE,
			m_isTurn,      
			TRUE          
		);
	}
	else if (m_GravityDir == PlayerGravityDir::LEFT)
	{
		DrawBillboard3D(
			m_Pos,
			0.5f,
			0.5f,
			m_Size,
			-DX_PI_F * 0.5f,
			GetAnimationHandle(anim),
			TRUE,
			m_isTurn,
			FALSE
		);
	}
	else if (m_GravityDir == PlayerGravityDir::RIGHT)
	{
		DrawBillboard3D(
			m_Pos,
			0.5f,
			0.5f,
			m_Size,
			DX_PI_F * 0.5f,
			GetAnimationHandle(anim),
			TRUE,
			m_isTurn,
			FALSE
		);
	}
	

}

void Player::Fin()
{
}

void Player::SetBulletManager(BulletManager* manager)
{
	m_BulletManager = manager;
}

void Player::ChangeAnimation(PlayerAnimationType anim)
{
	if (m_NowAnim == anim)
	{
		return;
	}

	m_NowAnim = anim;

	m_Animation[static_cast<int>(anim)].nowFrame = 0;
	m_Animation[static_cast<int>(anim)].timer = m_Animation[static_cast<int>(anim)].interval;
}

void Player::CheckHitStageObjects(const std::vector<StageObject*>& stageObjects)
{
	// 移動前の座標に戻す
	m_Pos = m_PrevPos;

	// X軸だけ移動させて当たり判定
	m_Pos.x += m_Move.x;
	for (auto obj : stageObjects)
	{
		const CollisionAABB* objAABB = obj->GetAABB();
		if (!objAABB) continue;

		if (m_AABB->CheckAABB(objAABB))
		{
			m_Pos.x = m_PrevPos.x;

			// 重力方向←
			if (m_GravityDir == PlayerGravityDir::LEFT)
			{
				if (m_Move.x < 0.0f)
				{
					m_Move.x = 0.0f;
					m_IsGround = true;
				}
				else if (m_Move.x > 0.0f)
				{
					m_Move.x = 0.0f;
					m_IsGround = false;
				}
			}
			// 重力方向→
			else if (m_GravityDir == PlayerGravityDir::RIGHT)
			{
				if (m_Move.x > 0.0f)
				{
					m_Move.x = 0.0f;
					m_IsGround = true;
				}
				else if (m_Move.x < 0.0f)
				{
					m_Move.x = 0.0f;
					m_IsGround = false;
				}
			}
		}
	}

	// Y軸だけ移動させて当たり判定
	m_Pos.y += m_Move.y;

	for (auto obj : stageObjects)
	{
		const CollisionAABB* objAABB = obj->GetAABB();
		if (!objAABB) continue;

		if (m_AABB->CheckAABB(objAABB))
		{
			// 衝突したので移動前のY座標に戻す
			m_Pos.y = m_PrevPos.y;

			if (m_GravityDir == PlayerGravityDir::DOWN ||
				m_GravityDir == PlayerGravityDir::UP)
			{
				// 重力↓
				if (m_GravityDir == PlayerGravityDir::DOWN)
				{
					if (m_Move.y < 0.0f)
					{
						m_Move.y = 0.0f;
						m_IsGround = true;
					}
					else if (m_Move.y > 0.0f)
					{
						m_Move.y = 0.0f;
						m_IsGround = false;
					}
				}

				// 重力↑
				else if (m_GravityDir == PlayerGravityDir::UP)
				{
					if (m_Move.y > 0.0f)
					{
						m_Move.y = 0.0f;
						m_IsGround = true;
					}
					else if (m_Move.y < 0.0f)
					{
						m_Move.y = 0.0f;
						m_IsGround = false;
					}
				}
			}

			else if (m_GravityDir == PlayerGravityDir::LEFT ||
				m_GravityDir == PlayerGravityDir::RIGHT)
			{
				m_Move.y = 0.0f;
			}
		}
	}

	// Z軸だけ移動させて当たり判定
	m_Pos.z += m_Move.z;
	for (auto obj : stageObjects)
	{
		const CollisionAABB* objAABB = obj->GetAABB();
		if (!objAABB) continue;

		if (m_AABB->CheckAABB(objAABB))
		{
			m_Pos.z = m_PrevPos.z;
		}
	}
}