#pragma once
#include "../BangerState.h"

class BangerFall
	:public BangerState
{
public:
	explicit BangerFall(Banger* e);
	~BangerFall() = default;

	void onCollision(::SidesCollision side) override;
	void update(float dt) override;
	::StateBanger getState() override;
};
