#pragma once
#ifndef __GAME_TIME__
#define __GAME_TIME__

#include <Windows.h>

class GameTime
{
private:
	LARGE_INTEGER m_StartTime, m_EndTime, m_Delta, m_ClockRate;
	static GameTime* m_Instance;

public:
	GameTime() = default;
	void StartCounter();
	float GetCounter();
	static GameTime* GetInstance();
	~GameTime();

};

#endif
