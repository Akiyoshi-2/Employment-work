#pragma once
#include "CameraBase.h"

enum CameraType
{
	FIXED_CAMERA,
	FOLLOW_CAMERA,
	CAMERA_TYPE_MAX,
	CAMERA_NONE = -1,
};

class CameraManager
{
public:
	CameraManager();
	~CameraManager();

	static void CreateInstance() { if (!m_instance) m_instance = new CameraManager; }
	static CameraManager* GetInstance() { return m_instance; }
	static void DeleteInstance() { if (m_instance) delete m_instance; m_instance = nullptr; }

	void Init();
	void Load();
	void Start();
	void Step();
	void Update();
	void Draw();
	void Fin();

	void CreateCamera(CameraType type);

	CameraBase* GetCamera(CameraType type) { return m_Camera[type]; }

	// 追従カメラモードに切り替える
	void ChangeFollowingMode();
	// 追従カメラモードを解除する
	void ReleaseFollowingMode();
	// 追従カメラモード
	bool IsFollowingMode() { return m_IsFollowing; }

private:
	static CameraManager* m_instance;

	CameraBase* m_Camera[CAMERA_TYPE_MAX];

	bool m_IsFollowing;	// 追従中
};
