#pragma once
#include "PlayScene.h"
#include "../SceneManager.h"
#include "../../Input/Input.h"
#include "../../Collision/CollisionManager.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerManager.h"
#include "../../Bullet/BulletManager.h"
#include "../../Camera/CameraManager.h"
#include "../../Camera/FollowCamera.h"
#include "../../Floor/Floor.h"


PlayScene::PlayScene()
{
	m_Floor = nullptr;
}

PlayScene::~PlayScene()
{
	Fin();
}

void PlayScene::Init()
{
	// コリジョンマネージャー生成
	CollisionManager::CreateInstance();
	
	// 仮床
	m_Floor = new Floor;
	m_Floor->Init();


	// プレイヤーマネージャー
	PlayerManager::CreateInstance();
	PlayerManager* playerManager = PlayerManager::GetInstance();

	playerManager->CreatePlayer();

	Player* player = playerManager->GetPlayer();

	if (player)
	{
		player->Init();

		player->SetFloor(m_Floor);
	}

	playerManager->Init();

	// カメラマネージャー
	CameraManager::CreateInstance();
	CameraManager::GetInstance()->CreateCamera(FOLLOW_CAMERA);
	CameraManager::GetInstance()->Init();

	// バレットマネージャー
	BulletManager::CreateInstance();
	BulletManager::GetInstance()->Init();

	playerManager->GetPlayer()->SetBulletManager(BulletManager::GetInstance());
}

void PlayScene::Load()
{
	// プレイヤーロード
	PlayerManager::GetInstance()->Load();
	// カメラロード
	CameraManager::GetInstance()->Load();
	// バレットロード
	BulletManager::GetInstance()->Load();

	// 仮床ロード
	m_Floor->Load();
}

void PlayScene::Start()
{
	// プレイヤー開始
	PlayerManager::GetInstance()->Start();
	// カメラ開始
	CameraManager::GetInstance()->Start();
	// バレット開始
	BulletManager::GetInstance()->Start();

	// 仮床開始
	m_Floor->Start();
}

void PlayScene::Step()
{
	// プレイヤーステップ
	PlayerManager::GetInstance()->Step();
	// カメラステップ
	CameraManager::GetInstance()->Step();
	// バレットステップ
	BulletManager::GetInstance()->Step();

	// 仮床ステップ
	m_Floor->Step();
}

void PlayScene::Update()
{
	// プレイヤー更新
	PlayerManager::GetInstance()->Update();
	// カメラ
	FollowCamera* camera = dynamic_cast<FollowCamera*>(
		CameraManager::GetInstance()->GetCamera(FOLLOW_CAMERA));

	if (camera)
	{
		camera->SetTargetPos(PlayerManager::GetInstance()->GetPlayer()->GetPos());
	}

	CameraManager::GetInstance()->Update();
	
	// 仮床更新
	m_Floor->Update();

	// バレット更新
	BulletManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	// 仮床描画
	m_Floor->Draw();


	// プレイヤー描画
	PlayerManager::GetInstance()->Draw();
	// カメラ描画
	CameraManager::GetInstance()->Draw();
	// バレット描画
	BulletManager::GetInstance()->Draw();

	// 当たり判定描画
	CollisionManager::GetInstance()->Draw();
}

void PlayScene::Fin()
{
	// プレイヤー終了
	PlayerManager::DeleteInstace();
	// カメラ終了
	CameraManager::DeleteInstance();

	// コリジョンマネージャー削除
	CollisionManager::DeleteInstance();

	// バレット終了
	BulletManager::DeleteInstance();

	// 仮床削除
	delete m_Floor;
}