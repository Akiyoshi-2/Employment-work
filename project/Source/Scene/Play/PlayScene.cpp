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
#include "../../StageObject/StageObjectManager.h"
#include "../../Stage/StageManager.h"


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
	
	// プレイヤーマネージャー
	PlayerManager::CreateInstance();
	PlayerManager* playerManager = PlayerManager::GetInstance();

	playerManager->CreatePlayer();

	Player* player = playerManager->GetPlayer();

	if (player)
	{
		player->Init();
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

	// ステージオブジェクト
	StageObjectManager::CreateInstance();
	StageObjectManager::GetInstance()->Init();

	// ステージマネージャー
	StageManager::CreateInstance();
}

void PlayScene::Load()
{
	// プレイヤーロード
	PlayerManager::GetInstance()->Load();
	// カメラロード
	CameraManager::GetInstance()->Load();
	// バレットロード
	BulletManager::GetInstance()->Load();

	// ステージオブジェクトロード
	StageObjectManager::GetInstance()->Load();
	// ステージロード
	StageManager::GetInstance()->Load("Data/Stage/機械惑星.json");
}

void PlayScene::Start()
{
	// ステージ開始
	StageManager::GetInstance()->Start();

	// ステージオブジェクト開始
	StageObjectManager::GetInstance()->Start();

	// プレイヤー開始
	PlayerManager::GetInstance()->Start();
	// カメラ開始
	CameraManager::GetInstance()->Start();
	// バレット開始
	BulletManager::GetInstance()->Start();

}

void PlayScene::Step()
{
	// プレイヤーステップ
	PlayerManager::GetInstance()->Step();
	// カメラステップ
	CameraManager::GetInstance()->Step();
	// バレットステップ
	BulletManager::GetInstance()->Step();

	//当たり判定
	CollisionManager::GetInstance()->CheckCollision();

}

void PlayScene::Update()
{
	// ステージオブジェクト更新
	StageObjectManager::GetInstance()->Update();

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
	
	// バレット更新
	BulletManager::GetInstance()->Update();
}

void PlayScene::Draw()
{
	// ステージオブジェクト描画
	StageObjectManager::GetInstance()->Draw();


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
	// ステージオブジェクト削除
	StageObjectManager::DeleteInstance();
	// ステージ削除
	StageManager::DeleteInstance();

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