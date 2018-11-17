#include "DieState.h"
#include "../../GamePlayer.h"


void DieState::update(float dt)
{
	gp->getAnimation()->setAnimation(20, 3, 0.15, false);
}

StateName DieState::getState()
{
	return Die;
}
