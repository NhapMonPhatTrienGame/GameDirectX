#pragma once
#include "../Banger.h"

class Banger;

class BangerState
{
protected:
	Banger *banger;
	float translateY;


public:
	explicit BangerState(Banger * banger);
	virtual ~BangerState() = default;

	virtual ::StateBanger getState() = 0;
	virtual void onCollision(::SidesCollision side);
	virtual void update(float dt);

};