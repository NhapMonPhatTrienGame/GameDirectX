#pragma once
#include "Brick.h"

class Stairs
	:public Brick
{
protected:
	const char* fileName() override;
	int totalFrame() override;
	int row() override;
	int column() override;
	float timePerFrame() override;

public:
	explicit Stairs(D3DXVECTOR3 pos);
	~Stairs() = default;
	
};
