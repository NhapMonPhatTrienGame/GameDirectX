#include "GunnerAttack.h"
#include "../GunnerStand/GunnerStand.h"
#include "../../../Banger/BangerBullet/BangerBullet.h"
#include <iostream>
#include "../../../../../GunnerAttackBullet.h"

GunnerAttack::GunnerAttack(Gunner* headGunner) :GunnerState(headGunner)
{
	this->pGunner->setVx(0);
	this->pGunner->setVy(200);
	timeAttack = 0;
	count = 0;
}

::StateGunner GunnerAttack::getState()
{
	return StateGunner::Attack;
}


void GunnerAttack::update(float dt)
{
	timeAttack += dt;
	if (timeAttack >= 0.45f)
	{
		timeAttack = 0;
		count++;

		if (count > 1)
		{
			pGunner->setState(new GunnerAttackBullet(pGunner));
			return;
		}

		if (pGunner->getGunnerBullet()->size() < 3)
		{
			if (count == 1)
			{
				auto* ebullet = new GunnerBullet();
				pGunner->getGunnerBullet()->push_back(ebullet);
			}
			
		}

		float posX = 0;
		float posY = pGunner->getBound().top;

		if (count == 1)
		{
			posY += 17;
			if (pGunner->getReverse())
				posX = pGunner->getBound().right;
			else
				posX = pGunner->getBound().left;
		}
		
		pGunner->getGunnerBullet()->at(count)->newBullet(posX, posY, pGunner->getReverse());
	}
}