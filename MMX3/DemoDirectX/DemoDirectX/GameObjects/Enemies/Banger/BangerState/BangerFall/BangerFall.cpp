#include "BangerFall.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerStand/BangerStand.h"

BangerFall::BangerFall(Banger * e) :BangerState(e)
{
	translateY = 25.0f;
	e->setVy(0);
}

void BangerFall::onCollision(::SidesCollision side)
{
	if (side == SidesCollision::Bottom)
		banger->setState(new BangerStand(banger));
}

void BangerFall::update(float dt)
{
	banger->addVy(translateY);
	if (banger->getVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		banger->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}

::StateBanger BangerFall::getState()
{
	return ::StateBanger::Fall;
}
