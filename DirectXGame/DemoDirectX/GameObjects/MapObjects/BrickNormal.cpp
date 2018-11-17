#include "BrickNormal.h"

BrickNormal::BrickNormal(D3DXVECTOR3 position)
{
	Init(position);
}

const char* BrickNormal::fileName()
{
	return "Resources/normalbrick.png";
}

int BrickNormal::totalFrame()
{
	return 1;
}

int BrickNormal::row()
{
	return 1;
}

int BrickNormal::column()
{
	return 1;
}

float BrickNormal::timePerFrame()
{
	return 1.0f;
}
