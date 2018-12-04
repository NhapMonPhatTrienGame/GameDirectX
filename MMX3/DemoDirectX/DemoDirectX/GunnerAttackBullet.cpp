#include "GunnerAttackBullet.h"
#include "GameObjects/Enemies/Gunner/GunnerState/GunnerStand/GunnerStand.h"
#include "GameObjects/Enemies/Banger/BangerBullet/BangerBullet.h"


GunnerAttackBullet::GunnerAttackBullet(Gunner* pGunner):GunnerState(pGunner)
{
	timeAttack = 0;
	count = 1;
}

::StateGunner GunnerAttackBullet::getState()
{
	return StateGunner::AttackBullet;
}

void GunnerAttackBullet::update(float dt)
{
	timeAttack += dt;
	if(timeAttack > 1.0f)
	{
		timeAttack = 0;
		count++;

		if(count > 4)
		{
			pGunner->setState(new GunnerStand(pGunner));
			return;
		}

		if(pGunner->getGunnerBullet()->size() < 5)
		{
			auto* ebullet = new BangerBullet();
			pGunner->getGunnerBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = pGunner->getBound().top;

		if(count < 5)
		{
			if (pGunner->getReverse())
				posX = pGunner->getBound().right - 16;
			else
				posX = pGunner->getBound().left + 16;
		}

		pGunner->getGunnerBullet()->at(count)->newBullet(posX, posY, pGunner->getReverse());
	}
}