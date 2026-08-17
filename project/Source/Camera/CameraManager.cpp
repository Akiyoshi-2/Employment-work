#include "DxLib.h"
#include "CameraManager.h"
#include "Camera.h"
#include "FollowCamera.h"

CameraManager* CameraManager::m_instance = nullptr;

CameraManager::CameraManager()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		m_Camera[i] = nullptr;
	}

	m_IsFollowing = false;
}

CameraManager::~CameraManager()
{
}

void CameraManager::CreateCamera(CameraType type)
{
	if (m_Camera[type] != nullptr)
	{
		return;
	}

	switch (type)
	{
	case FIXED_CAMERA:
		m_Camera[type] = new Camera();
		break;
	case FOLLOW_CAMERA:
		m_Camera[type] = new FollowCamera();
		break;
	
	}
}

void CameraManager::Init()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		if (m_Camera[i])
		{
			m_Camera[i]->Init();
		}
	}
}

void CameraManager::Load()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		if (m_Camera[i])
		{
			m_Camera[i]->Load();
		}
	}
}

void CameraManager::Start()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		if (m_Camera[i])
		{
			m_Camera[i]->Start();
		}
	}
}

void CameraManager::Step()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		if (m_Camera[i])
		{
			m_Camera[i]->Step();
		}
	}
}

void CameraManager::Update()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		if (m_Camera[i])
		{
			m_Camera[i]->Update();
		}
	}
}

void CameraManager::Draw()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{
		if (m_Camera[i])
		{
			m_Camera[i]->Draw();
		}
	}
}

void CameraManager::Fin()
{
	for (int i = 0; i < CAMERA_TYPE_MAX; i++)
	{	
		if (m_Camera[i])
		{
			m_Camera[i]->Fin();
			delete m_Camera[i];
			m_Camera[i] = nullptr;
		}
	}
}

void CameraManager::ChangeFollowingMode()
{
	m_IsFollowing = true;
}

void CameraManager::ReleaseFollowingMode()
{
	m_IsFollowing = false;
}