#pragma once
#include "DxLib.h"
#include "CameraBase.h"

class Player;

class FollowCamera : public CameraBase
{
public:
	FollowCamera();
	~FollowCamera();

	void Init() override;
	void Load() override;
	void Start() override;
	void Step() override;
	void Update() override;
	void Draw() override;
	void Fin() override;

	void SetTargetPos(VECTOR targetPos);

	void SetOffset(VECTOR offset);

private:
	VECTOR m_TargetPos;
	VECTOR m_Offset;

};
