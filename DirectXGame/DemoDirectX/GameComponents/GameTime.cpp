#include "GameTime.h"

GameTime* GameTime::m_Instance = nullptr;

GameTime* GameTime::GetInstance()
{
	if (!m_Instance)
		m_Instance = new GameTime();

	return m_Instance;
}

GameTime::~GameTime()
{
	if(m_Instance)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

void GameTime::StartCounter()
{
	if (!QueryPerformanceFrequency(&m_ClockRate))
		return;

	QueryPerformanceCounter(&m_StartTime);
}

float GameTime::GetCounter()
{
	QueryPerformanceCounter(&m_EndTime);
	m_Delta.QuadPart = m_EndTime.QuadPart - m_StartTime.QuadPart;

	return (float(m_Delta.QuadPart) / m_ClockRate.QuadPart);
}
