#include "DxLib.h"
#include "FollowCamera.h"


#define CAMERA_NEAR_CLIP 1.0f
#define CAMERA_FAR_CLIP 1000.0f

FollowCamera::FollowCamera()
{
	m_Pos = VGet(0.0f, 20.0f, -20.0f);

	m_Target = VGet(0.0f, 0.0f, 0.0f);

	m_Offset = VGet(0.0f, 40.0f, -100.0f);
}

FollowCamera::~FollowCamera()
{
}

void FollowCamera::Init()
{
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);
}

void FollowCamera::Load()
{

}

void FollowCamera::Start()
{

}

void FollowCamera::Step()
{

}

void FollowCamera::Update()
{
	m_Pos = VAdd(m_TargetPos, m_Offset);

	SetCameraPositionAndTarget_UpVecY(m_Pos, m_TargetPos);
}

void FollowCamera::Draw()
{

}

void FollowCamera::Fin()
{

}

void FollowCamera::SetTargetPos(VECTOR targetpos)
{
	m_TargetPos = targetpos;
}

void FollowCamera::SetOffset(VECTOR offset)
{
	m_Offset = offset;
}