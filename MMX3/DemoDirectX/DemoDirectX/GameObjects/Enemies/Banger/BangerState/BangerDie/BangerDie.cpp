#include "BangerDie.h"

::StateBanger BangerDie::getState()
{
	return StateBanger::Die;
}

void BangerDie::update(float dt)
{
	banger->addVy(translateY);

	timeDie += dt;
	if(timeDie >= 0.45f)
		banger->setDraw(false);
}
