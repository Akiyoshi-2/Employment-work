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

	/*m_GravityUpHandle = -1;
	m_GravityDownHandle = -1;
	m_GravityLeftHandle = -1;
	m_GravityRightHandle = -1;*/
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

	// 重力方向変更画面の画像読み込み
	/*m_GravityUpHandle = LoadGraph("Data/UI/Image/GravityDir_UP.png");
	m_GravityDownHandle = LoadGraph("Data/UI/Image/GravityDir_DOWN.png");
	m_GravityLeftHandle = LoadGraph("Data/UI/Image/GravityDir_LEFT.png");
	m_GravityRightHandle = LoadGraph("Data/UI/Image/GravityDir_RIGHT.png");*/
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

	// 重力方向変更画面の画像削除
	/*DeleteGraph(m_GravityUpHandle);
	DeleteGraph(m_GravityDownHandle);
	DeleteGraph(m_GravityLeftHandle);
	DeleteGraph(m_GravityRightHandle);*/
}

// 重力方向変更中の画面描画
//void PlayScene::DrawGravityChange()
//{
//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 180);
//
//	DrawBox(0, 0, 1600, 900, GetColor(0, 0, 0), TRUE);
//
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//
//	DrawString(735, 120, "GRAVITY CHANGE", GetColor(255, 255, 255), 0);
//
//	// 重力方向変更の画像描画
//	// ↑
//	DrawGraph(672, 160, m_GravityUpHandle, TRUE);
//
//	// ←
//	DrawGraph(500, 320, m_GravityLeftHandle, TRUE);
//
//	// →
//	DrawGraph(846, 320, m_GravityRightHandle, TRUE);
//
//	// ↓
//	DrawGraph(672, 480, m_GravityDownHandle, TRUE);
//
//	// X：キャンセル
//	DrawString(930, 680, "X : CANCEL", GetColor(255, 255, 255), 0);
//}