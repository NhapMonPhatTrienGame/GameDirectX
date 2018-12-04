#include "BleedState.hpp"
#include "../StandState/StandState.h"

BleedState::BleedState(GamePlayer* gp, int Direction) :GameState(gp)
{
	gp->setVx(30.0f*Direction);
	gp->setVy(5.0f);
	timeBleed = 0.0f;
}

void BleedState::update(float dt)
{
	if (gp->getAnimation()->getCurrentColumn() >= 8)
		gp->setState(new StandState(gp));
}

PlayerState BleedState::getState()
{
	return PlayerState::Bleed;
}
