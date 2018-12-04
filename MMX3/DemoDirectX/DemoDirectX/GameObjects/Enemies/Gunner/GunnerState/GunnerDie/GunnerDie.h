#ifndef _HEAD_GUNNER_DIE_H
#define _HEAD_GUNNER_DIE_H
#include "../GunnerState.h"

class GunnerDie : public GunnerState
{
private:
	float timeDie;

public:
	explicit GunnerDie(Gunner* headGunner);
	~GunnerDie() = default;

	::StateGunner getState() override;
	void update(float dt) override;

};

#endif
