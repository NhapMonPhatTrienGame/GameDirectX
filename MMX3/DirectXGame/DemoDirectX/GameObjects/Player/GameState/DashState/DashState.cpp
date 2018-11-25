#include "DashState.h"
#include <iostream>
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"

DashState::DashState(GamePlayer* gp) : GameState(gp)
{
	translateX = 25.0f;
	timePress = 0;
}

void DashState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	timePress += dt;
	if (timePress <= 0.45f)
	{
		if (!gp->getReverse())
		{
			gp->setVx(Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_LEFT])
				gp->setState(new StandState(gp));
		}
		else
		{
			gp->setVx(-Define::PLAYER_MAX_SLIDE_SPEED);
			if (keys[VK_RIGHT])
				gp->setState(new StandState(gp));
		}
	}
	else
		gp->setState(new StandState(gp));
}

void DashState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Left:
	case Entity::Right:
		{
			gp->setState(new StandState(gp));
			break;
		}
	default: break;
	}
}

GamePlayer::StateName DashState::getState()
{
	return GamePlayer::Dash;
}
