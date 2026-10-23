#include "ShootingEnemy.h"
#include "../../Collision/CollisionAABB.h"
#include "../../StageObject/StageObject.h"
#include "../../StageObject/StageObjectManager.h"
#include "../../Player/Player.h"
#include "../../Player/PlayerManager.h"
#include "../../MyMath/MyMath.h"
#include <vector>

#define MOVE_SPEED 0.3

ShootingEnemy::ShootingEnemy()
{
}

ShootingEnemy::~ShootingEnemy()
{
}

void ShootingEnemy::Init()
{
	m_HP = 30;

	m_Surface = ENEMY_SURFACE_NONE;
	m_Dir = ENEMY_DIR_NONE;

	m_Move = VGet(0.0f, 0.0f, 0.0f);

	m_AABB = new CollisionAABB();

	m_AABB->SetTargetPos(&m_Pos);
	m_AABB->SetLocalPos(VGet(0.0f, 0.0f, 0.0f));
	m_AABB->SetSize(VGet(1.0f, 1.0f, 1.0f));
}

void ShootingEnemy::Load()
{
	m_Handle = MV1LoadModel("Data/Enemy/Machine/まだ作ってない");
}

void ShootingEnemy::Start()
{

}

void ShootingEnemy::Step()
{
	if (m_AABB == nullptr) return;

	const std::vector<StageObject*>& stageObjects = StageObjectManager::GetInstance()->GetStageObjects();

	// 移動前の座標を保存
	VECTOR prrevPos = m_Pos;
	VECTOR nextPos = MyMath::VecAdd(m_Pos, m_Move);

	bool hasSurface = HasSurfaceAhead(nextPos);

	bool isHit = false;

	// ステージとの当たり判定
	for (auto obj : stageObjects)
	{
		if (obj == nullptr) continue;
		
		const CollisionAABB* objAABB = obj->GetAABB();

		if (objAABB == nullptr) continue;

		if (m_AABB->CheckAABB(objAABB))
		{
			isHit = true;
			break;
		}
	}

}