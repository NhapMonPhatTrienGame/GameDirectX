#include "BangerAttack.h"
#include "../BangerJump/BangerJump.h"

BangerAttack::BangerAttack(Banger* e) : BangerState(e)
{
	timeAttack = 0.0f;
	count = -1;
}

void BangerAttack::update(float dt)
{
	timeAttack += dt;

	if(timeAttack >= 0.45f)
	{
		timeAttack = 0.0f;
		count++;

		if (count >= 3)
		{
			banger->setState(new BangerJump(banger));
			return;
		}

		if (banger->getBangerBullet()->size() < 3)
		{
			auto* ebullet = new BangerBullet();
			banger->getBangerBullet()->push_back(ebullet);
		}

		float posX;
		float posY = banger->getBound().top + 8;

		if (banger->getReverse())
			posX = banger->getBound().right - 8;
		else
			posX = banger->getBound().left + 8;

		banger->getBangerBullet()->at(count)->newBullet(posX, posY, banger->getReverse());
	}
}

::StateBanger BangerAttack::getState()
{
	return ::StateBanger::Attack;
}
