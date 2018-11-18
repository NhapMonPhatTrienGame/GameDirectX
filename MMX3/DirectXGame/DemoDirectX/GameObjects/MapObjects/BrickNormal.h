#pragma once
#include "Brick.h"

class BrickNormal : public Brick
{
public:
	~BrickNormal() = default;

	explicit BrickNormal(D3DXVECTOR3 position);

	const char* fileName() override;
	int totalFrame() override;
	int row() override;
	int column() override;
	float timePerFrame() override;
};
