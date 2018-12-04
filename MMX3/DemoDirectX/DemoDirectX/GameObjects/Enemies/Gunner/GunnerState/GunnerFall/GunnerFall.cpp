#include "GunnerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../GunnerStand/GunnerStand.h"

GunnerFall::GunnerFall(Gunner* headGunner) :GunnerState(headGunner)
{
	this->pGunner->setVy(0);
	translateY = 25.0f;
}

::StateGunner GunnerFall::getState()
{
	return StateGunner::Fall;
}

void GunnerFall::onCollision(::SidesCollision side)
{
	if (side == SidesCollision::Bottom)
		pGunner->setState(new GunnerStand(pGunner));
}

void GunnerFall::update(float dt)
{
	pGunner->addVy(translateY);
	if (pGunner->getVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		pGunner->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}
