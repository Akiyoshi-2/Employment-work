#include "DxLib.h"
#include "Player.h"
#include "../Input/Input.h"
#include "../Bullet/PlayerBullet/PlayerBullet.h"
#include "../Collision/CollisionAABB.h"
#include "../Floor/Floor.h"


#define MOVE_SPEED		0.4f
#define JUMP_POWER		2.5f
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
	m_Size = 7.5;	// プレイヤーサイズ

	m_Pos = VGet(0.0f, 0.0f, 0.0f);
	m_Move = VGet(0.0f, 0.0f, 0.0f);
	
	m_isTurn = false;

	m_IsGround = false;

	m_NowAnim = PlayerAnimationType::IDLE;

	m_BulletManager = nullptr;

	m_BulletCoolTime = 0.0f;
	m_BulletInterval = 7.0f;

	m_Floor = nullptr;

	m_GravityDir = PlayerGravityDir::DOWN;
}

Player::~Player()
{
}

void Player::Init()
{
	m_Collision.SetTargetPos(&m_Pos);

	// プレイヤーの中心からのオフセット
	m_Collision.SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	// プレイヤーの大きさ
	m_Collision.SetSize(VGet(4.0f, 7.0f, 1.0f));
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

}

void Player::Step()
{

}

void Player::Update()
{
	if (m_GravityDir == PlayerGravityDir::DOWN)
	{
		m_Move.x = 0.0f;
		if (!m_IsGround)
		{
			m_Move.y -= GRAVITY;
		}
		else
		{
			m_Move.y = 0.0f;
		}
		m_Move.z = 0.0f;

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

		m_Pos.x += m_Move.x;
		m_Pos.z += m_Move.z;

		float beforeY = m_Pos.y;

		m_Pos.y += m_Move.y;

		if (m_Move.y > 0)
		{
			m_IsGround = false;
		}

		// 床との当たり判定
		if (m_Floor != nullptr)
		{
			if (m_Collision.CheckAABB(m_Floor->GetCollision()))
			{
				if (m_Move.y <= 0.0f)
				{
					m_Pos.y =
						m_Floor->GetPos().y
						+ m_Floor->GetCollision()->GetSize().y * 0.5f
						+ m_Collision.GetSize().y * 0.5f;


					m_Move.y = 0.0f;

					m_IsGround = true;
				}
			}
			else
			{
				m_IsGround = false;
			}
		}

		// アニメーション切り替え
		if (m_Move.y != 0)
		{
			m_NowAnim = PlayerAnimationType::JUMP;
		}
		else if (m_IsGround == true && m_Move.x != 0.0f || m_Move.z != 0.0f)
		{
			m_NowAnim = PlayerAnimationType::RUN;
		}
		else
		{
			m_NowAnim = PlayerAnimationType::IDLE;
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
	else if (m_GravityDir == PlayerGravityDir::UP)
	{

	}
	else if (m_GravityDir == PlayerGravityDir::LEFT)
	{

	}
	else if (m_GravityDir == PlayerGravityDir::RIGHT)
	{

	}

	

	UpdateAnimation(&m_Animation[static_cast<int>(m_NowAnim)]);
}

void Player::Draw()
{		
	AnimationData* anim = &m_Animation[static_cast<int>(m_NowAnim)];

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
	m_Animation[static_cast<int>(anim)].timer =
		m_Animation[static_cast<int>(anim)].interval;
}

void Player::SetFloor(Floor* floor)
{
	m_Floor = floor;
}