#ifndef GUNNER_STATE_H
#define GUNNER_STATE_H

#include "../Gunner.h"

class Gunner;

class GunnerState
{
protected:
	Gunner* pGunner;
	int count;
	float timeAttack;
	float translateY;

public:
	explicit GunnerState(Gunner* headGunner);
	virtual ~GunnerState() = default;

	virtual ::StateGunner getState() = 0;
	virtual void onCollision(::SidesCollision side);
	virtual void update(float dt);

};
#endif
