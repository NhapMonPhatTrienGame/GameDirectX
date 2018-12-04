#include "BangerJump.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerFall/BangerFall.h"

BangerJump::BangerJump(Banger* e) :BangerState(e)
{
	e->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	if (e->getReverse())
		e->setVx(200);
	else
		e->setVx(-200);

	translateY = 15.0f;
}

void BangerJump::onCollision(::SidesCollision side)
{
	switch (side)
	{
	case SidesCollision::Left: case SidesCollision::Right: case SidesCollision::Bottom:
		break;
	case SidesCollision::Top:
		banger->setState(new BangerFall(banger));
		break;
	default: break;
	}
}

void BangerJump::update(float dt)
{	
	banger->addVy(translateY);
	if (banger->getVy() > 0)
	{
		banger->setState(new BangerFall(banger));
	}
}

::StateBanger BangerJump::getState()
{
	return StateBanger::Jump;
}
