#include "BrickGold.h"

BrickGold::BrickGold(D3DXVECTOR3 position)
{
	Init(position);
}

const char* BrickGold::fileName()
{
	return "Resources/goldbrick.png";
}

int BrickGold::totalFrame()
{
	return 4;
}

int BrickGold::row()
{
	return 1;
}

int BrickGold::column()
{
	return 4;
}

float BrickGold::timePerFrame()
{
	return 0.3f;
}
