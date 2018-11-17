#include "Stairs.h"

const char* Stairs::fileName()
{
	return "Resources/Stairs.png";
}

int Stairs::totalFrame()
{
	return 1;
}

int Stairs::row()
{
	return 1;
}

int Stairs::column()
{
	return 1;
}

float Stairs::timePerFrame()
{
	return 0;
}

Stairs::Stairs(D3DXVECTOR3 pos)
{
	this->Init(pos);
}
