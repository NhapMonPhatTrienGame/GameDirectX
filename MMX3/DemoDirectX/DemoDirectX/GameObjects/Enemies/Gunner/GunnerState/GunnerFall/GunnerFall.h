#ifndef _HEAD_GUNNER_FALL_STATE_H
#define _HEAD_GUNNER_FALL_STATE_H
#include "../GunnerState.h"


class GunnerFall :public GunnerState
{
public:
	explicit GunnerFall(Gunner* headGunner);
	~GunnerFall() = default;
	::StateGunner getState() override;
	void onCollision(::SidesCollision side) override;
	void update(float dt) override;
};

#endif