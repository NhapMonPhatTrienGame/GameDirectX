#include "BangerStand.h"
#include "../../../../../GameDefines/GameDefine.h"
#include "../BangerAttack/BangerAttack.h"

BangerStand::BangerStand(Banger* e) : BangerState(e)
{
	e->setVx(0);
	e->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
	timePerShoot = 0.0f;
}


::StateBanger BangerStand::getState()
{
	return ::StateBanger::Stand;
}

void BangerStand::update(float dt)
{
	timePerShoot += dt;
	if (timePerShoot > 1.0f)
	{
		banger->setState(new BangerAttack(banger));
	}
}
