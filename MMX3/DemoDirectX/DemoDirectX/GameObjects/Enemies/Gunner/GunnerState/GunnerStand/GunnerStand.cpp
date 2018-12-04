#include  "GunnerStand.h"
#include "../GunnerAttack/GunnerAttack.h"
#include "../GunnerAttack/GunnerAttackRocket.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"

GunnerStand::GunnerStand(Gunner* headGunner) :GunnerState(headGunner)
{
	headGunner->setVx(0);
	headGunner->setVy(200);
	timeAttack = 0;
}

::StateGunner GunnerStand::getState()
{
	return StateGunner::Stand;
}

void GunnerStand::update(float dt)
{
	timeAttack += dt;
	if (timeAttack > 1.0f)
	{
		pGunner->setState(new GunnerAttackRocket(pGunner));
	}
}
