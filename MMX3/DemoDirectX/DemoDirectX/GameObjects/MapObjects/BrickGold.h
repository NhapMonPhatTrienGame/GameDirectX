#pragma once
#include "Brick.h"

class BrickGold : public Brick
{
public:
	explicit BrickGold(D3DXVECTOR3 position);
	~BrickGold() = default;

	const char* fileName() override;
	int totalFrame() override;
	int row() override;
	int column() override;
	float timePerFrame() override;
};
