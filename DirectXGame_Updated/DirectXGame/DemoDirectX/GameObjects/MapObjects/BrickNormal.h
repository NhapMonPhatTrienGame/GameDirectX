#pragma once
#include "Brick.h"
class BrickNormal : public Brick
{
public:
    ~BrickNormal() = default;

	explicit BrickNormal(D3DXVECTOR3 position);

	const char* FileName() override;
	int TotalFrame() override;
	int Row() override;
	int Column() override;
	float TimePerFrame() override;
};

