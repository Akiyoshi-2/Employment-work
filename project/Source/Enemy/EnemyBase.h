#pragma once
#include "DxLib.h"
#include <vector>

class CollisionAABB;
class StageObject;

// ìGÇÃê⁄ínñ 
enum EnemySurface
{
	ENEMY_SURFACE_FLOOR,
	ENEMY_SURFACE_WALL,
	ENEMY_SURFACE_CEILING,
	ENEMY_SURFACE_NONE = -1,
};

// ìGÇÃà⁄ìÆï˚å¸
enum EnemyDir
{
	ENEMY_DIR_LEFT,
	ENEMY_DIR_RIGHT,
	ENEMY_DIR_UP,
	ENEMY_DIR_DOWN,
	ENEMY_DIR_NONE = -1,
};

class EnemyBase
{
public:
	EnemyBase();
	virtual ~EnemyBase();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;

	virtual void Update();
	virtual void Draw();
	virtual void Fin();

	virtual EnemyBase* Clone() = 0;

	void SetTransform(VECTOR pos, VECTOR rot, VECTOR scale)
	{
		m_Pos = pos; m_Rot = rot; m_Scale = scale;

		// âÒì]Ç©ÇÁç°Ç¢ÇÈñ ÇîªíË
		SetSurfaceFromRotation();
	}
	void SetPos(VECTOR pos) { m_Pos = pos; }

protected:
	int m_Handle;
	VECTOR m_Pos;
	VECTOR m_Rot;
	VECTOR m_Scale;
	VECTOR m_Move;
	VECTOR m_PrevPos;

	CollisionAABB* m_AABB;

	EnemySurface m_Surface;
	EnemyDir m_Dir;

	void SetSurfaceFromRotation();
};

