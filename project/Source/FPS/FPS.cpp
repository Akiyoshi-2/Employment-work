#include "DxLib.h"
#include "FPS.h"

#define FPS_NUM (60)

#define FPS (60)

int FPSSystem::m_StartTime = 0;
int FPSSystem::m_Count = 0;
float FPSSystem::m_Fps = 0.0f;

void FPSSystem::Init()
{
	m_StartTime = GetNowCount();
	m_Count = 0;
	m_Fps = 0;
}

void FPSSystem::Update()
{
	if (m_Count == 0)
	{
		m_StartTime = GetNowCount();
	}

	if (m_Count == FPS_NUM)
	{
		int time = GetNowCount();

		m_Fps = 1000.f / ((time - m_StartTime) / (float)FPS_NUM);
		m_Count = 0;
		m_StartTime = time;
	}
	m_Count++;
}

void FPSSystem::Draw()
{
	DrawFormatString(0, 880, GetColor(255, 255, 255), "FPSy%.1fz", m_Fps);
}

void FPSSystem::WaitFPS()
{
	int takeTime = GetNowCount() - m_StartTime;

	int waitTime = m_Count * 1000 / FPS - takeTime;

	if (waitTime > 0)
	{
		Sleep(waitTime);
	}
}