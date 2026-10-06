#include "PlayerManager.h"
#include "Player.h"
#include "../StageObject/StageObjectManager.h"
#include "../Input/Input.h"

PlayerManager* PlayerManager::m_Instance = nullptr;

PlayerManager::PlayerManager()
{
	m_Player = nullptr;
	m_IsGravityChange = false;
}

PlayerManager::~PlayerManager()
{
	Fin();
}

void PlayerManager::CreatePlayer()
{
	if (m_Player == nullptr)
	{
		m_Player = new Player();
	}
}

void PlayerManager::Init()
{
	if (m_Player)
	{
		m_Player->Init();
	}
}

void PlayerManager::Load()
{
	if (m_Player)
	{
		m_Player->Load();
	}
}

void PlayerManager::Start()
{
	if (m_Player)
	{
		m_Player->Start();
	}
}

void PlayerManager::Step()
{
	if (m_Player)
	{
		m_Player->Step();
	}
}

void PlayerManager::Update()
{
	if (m_Player)
	{
		m_Player->Update();
	}
}

void PlayerManager::Draw()
{
	if (m_Player)
	{
		m_Player->Draw();
	}
}

void PlayerManager::Fin()
{
	if (m_Player)
	{
		delete m_Player;
		m_Player = nullptr;
	}
}

//void PlayerManager::GravityChange()
//{
//	if (!m_IsGravityChange)
//	{
//		// 重力方向変更画面を開く
//		if (Input::IsTriggerKey(Input::KEY_X))
//		{
//			m_IsGravityChange = true;
//		}
//
//		return;
//	}
//
//	// 重力方向変更画面を閉じる
//	if (Input::IsTriggerKey(Input::KEY_X))
//	{
//		m_IsGravityChange = false;
//		return;
//	}
//	// 重力方向選択
//	if (Input::IsTriggerKey(Input::KEY_W))
//	{
//		m_Player->SetGravityDir(Player::PlayerGravityDir::UP);
//
//		m_IsGravityChange = false;
//	}
//	else if (Input::IsTriggerKey(Input::KEY_S))
//	{
//		m_Player->SetGravityDir(Player::PlayerGravityDir::DOWN);
//
//		m_IsGravityChange = false;
//	}
//	else if (Input::IsTriggerKey(Input::KEY_A))
//	{
//		m_Player->SetGravityDir(Player::PlayerGravityDir::LEFT);
//
//		m_IsGravityChange = false;
//	}
//	else if (Input::IsTriggerKey(Input::KEY_D))
//	{
//		m_Player->SetGravityDir(Player::PlayerGravityDir::RIGHT);
//
//		m_IsGravityChange = false;
//	}
//}