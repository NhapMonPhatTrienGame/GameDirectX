#pragma once
#include "../BangerState.h"


class BangerStand :
	public BangerState
{
protected:
	float timePerShoot;

public:
	explicit BangerStand(Banger *e);
	~BangerStand() = default;

	::StateBanger getState() override;
	void update(float dt) override;


};
