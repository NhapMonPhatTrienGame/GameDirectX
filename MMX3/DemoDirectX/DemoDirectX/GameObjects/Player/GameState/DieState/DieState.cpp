#include "DieState.h"

DieState::DieState(GamePlayer* gp) :GameState(gp)
{
	gp->setVx(0);
	gp->setVy(0);
	timeDie = 0.0f;
}

void DieState::update(float dt)
{
	timeDie += dt;
	if (timeDie >= 3.0f)
	{
		gp->getAnimation()->setAnimation(20, 3, 0.3);
	}
		
}

PlayerState DieState::getState()
{
	return PlayerState::Die;
}
