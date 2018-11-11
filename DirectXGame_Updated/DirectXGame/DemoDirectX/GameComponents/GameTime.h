#pragma once
#ifndef __GAME_TIME__
#define __GAME_TIME__

#include <Windows.h>

class GameTime
{
	LARGE_INTEGER mStartTime, mEndTime, mDelta, mClockRate;
	static GameTime *mInstance;

public:
	GameTime() = default;
    void StartCounter();
    float GetCounter();
    static GameTime* GetInstance();
    ~GameTime() = default;
};

#endif

