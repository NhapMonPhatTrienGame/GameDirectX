#include "GunnerState.h"

GunnerState::GunnerState(Gunner* headGunner)
{
	this->pGunner = headGunner;
}

void GunnerState::onCollision(::SidesCollision side)
{
}

void GunnerState::update(float dt)
{
}
