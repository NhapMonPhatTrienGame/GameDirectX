#include "GameTime.h"

GameTime* GameTime::mInstance = nullptr;

GameTime::GameTime()
{}

GameTime::~GameTime()
{}

GameTime* GameTime::getInstance()
{
	if (mInstance == nullptr)
		mInstance = new GameTime();

	return mInstance;
}

float GameTime::getCounter()
{
	QueryPerformanceFrequency(&mEndTime);
	mDelta.QuadPart = mEndTime.QuadPart - mStartTime.QuadPart;

	return (float(mDelta.QuadPart) / mClockRate.QuadPart);
}

void GameTime::startCounter()
{
	if (!QueryPerformanceFrequency(&mClockRate))
		return;
	QueryPerformanceFrequency(&mStartTime);
}
