#include "DxLib.h"
#include "PlayerBullet.h"
#include "../../StageObject/StageObjectManager.h"

#define BULLET_OUT_X 1600
#define BULLET_OUT_Y 900

PlayerBullet::PlayerBullet()
{
   
}

PlayerBullet::~PlayerBullet()
{
	
}

void PlayerBullet::Init()
{
	m_AABB = new CollisionAABB();

	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));

	m_AABB->SetSize(VGet(0.5f, 0.5f, 0.5f));
}

void PlayerBullet::Load()
{
    m_Handle = LoadGraph("Data/Bullet/PlayerBullet.png");
}

void PlayerBullet::Start()
{
}

void PlayerBullet::Step()
{
}

void PlayerBullet::Update()
{
    // 基底クラスの移動処理
    BulletBase::Update();

	// ステージとの当たり判定
    auto stageObjects = StageObjectManager::GetInstance()->GetStageObjects();

    for (auto obj : stageObjects)
    {
		if (!obj) continue;

		const CollisionAABB* objAABB = obj->GetAABB();

        if (!objAABB)
            continue;

        // 弾とステージが当たった
        if (0)
        {
            SetDead();
            break;
        }
    }

    // 画面外に出たら削除
   /* if (m_Pos.x < -64 || m_Pos.x > BULLET_OUT_X + 64 ||
        m_Pos.y < -64 || m_Pos.y > BULLET_OUT_Y + 64)
    {
        SetDead();
    }*/
}

void PlayerBullet::Draw()
{
    DrawBillboard3D(
        m_Pos,
        0.5f,       // 画像中央(X)
        0.5f,       // 画像中央(Y)
        3.0f,       // サイズ
        0.0f,       // 回転
        m_Handle,
        TRUE,
        FALSE,      // 左右反転
        FALSE       // 上下反転
    );
}

void PlayerBullet::Fin()
{
}
