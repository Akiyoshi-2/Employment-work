#include "DxLib.h"
#include "Camera.h"

#define CAMERA_NEAR_CLIP 1.0f
#define CAMERA_FAR_CLIP 1000.0f

Camera::Camera()
{
	m_Pos = VGet(0.0f, 0.0f, 0.0f);

	m_Target = VGet(0.0f, 0.0f, 0.0f);
}

Camera::~Camera()
{
}

void Camera::Init()
{
	SetCameraNearFar(CAMERA_NEAR_CLIP, CAMERA_FAR_CLIP);

	SetCameraPositionAndTarget_UpVecY(m_Pos, m_Target);
}

void Camera::Load()
{

}
void Camera::Start()
{

}

void Camera::Step()
{

}

void Camera::Update()
{
	SetCameraPositionAndTarget_UpVecY(m_Pos, m_Target);
}

void Camera::Draw()
{

}

void Camera::Fin()
{

}

void Camera::SetPosition(VECTOR pos)
{
	m_Pos = pos;
}

void Camera::SetTarget(VECTOR target)
{
	m_Target = target;
}

