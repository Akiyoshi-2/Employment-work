#pragma once
#include "DxLib.h"

class CameraBase
{
public:
	CameraBase();
	virtual ~CameraBase();

	virtual void Init() = 0;
	virtual void Load() = 0;
	virtual void Start() = 0;
	virtual void Step() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	virtual void Fin() = 0;

	VECTOR GetTarget() { return m_Target; }

	void SetTarget(VECTOR target) { m_Target = target; }

protected:
	VECTOR m_Pos;
	VECTOR m_Target;
	VECTOR m_UpVec;
};
