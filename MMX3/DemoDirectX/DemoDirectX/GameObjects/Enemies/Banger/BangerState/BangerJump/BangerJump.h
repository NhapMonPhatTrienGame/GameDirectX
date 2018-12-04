#pragma once
#include "../BangerState.h"

class BangerJump :
	public BangerState
{
public:
	explicit BangerJump(Banger *e);
	~BangerJump() = default;

	void onCollision(::SidesCollision side) override;
	void update(float dt) override;
	::StateBanger getState() override;
};
