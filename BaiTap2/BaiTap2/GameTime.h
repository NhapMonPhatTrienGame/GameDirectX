#ifndef _GAME_TIME_H
#define _GAME_TIME_H
#include <Windows.h>

class GameTime
{
public:
	GameTime();
	~GameTime();
	static GameTime* getInstance();

	float getCounter();
	void startCounter();
private:
	static GameTime* mInstance;

	LARGE_INTEGER mStartTime, mEndTime, mDelta, mClockRate;

};

#endif