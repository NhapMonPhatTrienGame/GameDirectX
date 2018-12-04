#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"


void RunState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	if (keys[VK_RIGHT])
	{
		gp->setReverse(false);
		gp->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		gp->setReverse(true);
		gp->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		gp->setVx(0);
		gp->setState(new StandState(gp));
	}
}

void RunState::onCollision(SidesCollision side)
{
	switch (side)
	{
	case SidesCollision::Left: case SidesCollision::Right:
		gp->setState(new StandState(gp));
		break;
	default: break;
	}
}

PlayerState RunState::getState()
{
	return PlayerState::Run;
}
