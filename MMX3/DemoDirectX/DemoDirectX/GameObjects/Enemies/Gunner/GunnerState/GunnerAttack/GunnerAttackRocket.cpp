#include "GunnerAttackRocket.h"
#include "GunnerAttack.h"

GunnerAttackRocket::GunnerAttackRocket(Gunner* pGunner) :GunnerState(pGunner)
{
	pGunner->setVy(200);
	pGunner->setVx(0);
	timeAttack = 0;
	count = -1;
}

::StateGunner GunnerAttackRocket::getState()
{
	return StateGunner::AttackRocket;
}

void GunnerAttackRocket::update(float dt)
{
	timeAttack += dt;
	if (timeAttack >= 0.45f)
	{
		timeAttack = 0;
		count++;

		if (count > 0)
		{
			pGunner->setState(new GunnerAttack(pGunner));
			return;
		}

		if(pGunner->getGunnerBullet()->empty())
		{
			auto* ebullet = new GunnerBullet();
			pGunner->getGunnerBullet()->push_back(ebullet);
		}

		float posX = 0;
		float posY = pGunner->getBound().top + 12;

		if (count == 0)
		{
			if (pGunner->getReverse())
				posX = pGunner->getBound().right - 10;
			else
				posX = pGunner->getBound().left + 10;
		}

		pGunner->getGunnerBullet()->at(count)->newBullet(posX, posY, pGunner->getReverse());
	}
}