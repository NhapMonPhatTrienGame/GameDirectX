#include "HelitAttack.h"
#include "../HelitStand/HelitStand.h"

HelitAttack::HelitAttack(Helit* helit) :HelitState(helit)
{
	helit->setVy(0);
	helit->setVx(0);
	timeAttack = 0.0f;
	count = -1;
}

::StateHelit HelitAttack::getState()
{
	return StateHelit::Attack;
}

void HelitAttack::update(float dt)
{
	timeAttack += dt;
	if(timeAttack >= 0.4f)
	{
		timeAttack = 0;
		count++;

		if (count > 0)
		{
			helit->setState(new HelitStand(helit));
			return;
		}

		if(helit->getHelitBullet()->empty())
		{
			auto* bullet = new HelitBullet();
			helit->getHelitBullet()->push_back(bullet);
		}

		float posX = 0;
		float posY = helit->getBound().top + 35;

		if (count == 0)
		{
			if (helit->getReverse())
				posX = helit->getBound().right - 10;
			else
				posX = helit->getBound().left + 10;
		}

		helit->getHelitBullet()->at(count)->newBullet(posX, posY, helit->getReverse());
	}
}
