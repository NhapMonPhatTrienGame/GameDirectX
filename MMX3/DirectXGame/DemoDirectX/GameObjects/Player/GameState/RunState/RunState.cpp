﻿#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../GamePlayer.h"


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

StateName RunState::getState()
{
	return Running;
}

void RunState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Left:
	case Entity::Right:
	{
		gp->setState(new StandState(gp));
		//ko set ve stand loi va cham enemy
		//gp->setPosition(gp->getPosition());
		break;
	}
	default: break;
	}
}