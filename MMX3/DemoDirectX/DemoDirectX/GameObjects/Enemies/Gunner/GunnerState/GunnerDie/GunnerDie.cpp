#include "GunnerDie.h"
#include "../../../../../GameDefines/GameDefine.h"

GunnerDie::GunnerDie(Gunner* headGunner) :GunnerState(headGunner)
{
	pGunner->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	timeDie = 0;
	translateY = 25.0f;
}

::StateGunner GunnerDie::getState()
{
	return StateGunner::Die;
}

void GunnerDie::update(float dt)
{
	pGunner->addVy(translateY);
	
	timeDie += dt;
	if (timeDie >= 0.45f)
	{
		pGunner->setDraw(false);
		return;
	}
}