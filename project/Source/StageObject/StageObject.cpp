#include "StageObject.h"
#include <stdio.h>

StageObject::StageObject()
{
	m_Handle = -1;
	m_Pos = {};
	m_Rot = {};
	m_Scale = {};
	m_AABB = nullptr;
}

StageObject::~StageObject()
{
	Fin();
}

void StageObject::Start()
{
}

void StageObject::Load(const char* fileName)
{
	// m_Handle = MV1LoadModel(fileName);

	// デバッグ用 /////////////////////////////
	printf("LoadModel : %s\n", fileName);

	m_Handle = MV1LoadModel(fileName);

	printf("Model Handle : %d\n", m_Handle);
	///////////////////////////////////////////
}

void StageObject::Update()
{
	// デバッグ用
	 if (m_Handle == -1)
    {
        printfDx("Update ERROR : handle=-1\n");
        return;
    }
	//

	MV1SetPosition(m_Handle, m_Pos);
	MV1SetRotationXYZ(m_Handle, m_Rot);
	MV1SetScale(m_Handle, m_Scale);
}

void StageObject::Draw()
{
	// MV1DrawModel(m_Handle);

	// デバッグ用 ////////////
	if (m_Handle == -1)
	{
		printfDx("Draw ERROR: handle=-1\n");
		return;
	}

	MV1DrawModel(m_Handle);
	////////////////////////
}

void StageObject::Fin()
{
	if (m_Handle != -1)
	{
		MV1DeleteModel(m_Handle);
		m_Handle = -1;
	}
	if (m_AABB)
	{
		delete m_AABB;
		m_AABB = nullptr;
	}
}