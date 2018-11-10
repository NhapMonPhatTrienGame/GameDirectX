#pragma once
#include "Brick.h"

class BrickGold : public Brick
{
public:
	explicit BrickGold(D3DXVECTOR3 position);
    ~BrickGold() = default;

	const char* FileName() override;
	int TotalFrame() override;
	int Row() override;
	int Column() override;
	float TimePerFrame() override;
};