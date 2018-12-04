#include "FallState.h"
#include "../RunState/RunState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"

FallState::FallState(GamePlayer* gp, bool dash) : GameState(gp)
{
	gp->setVy(0);
	translateY = 25.0f;
	Pressed = dash;
}

void FallState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	float speed = 0.0f;
	if (keys[VK_RIGHT])
	{
		gp->setReverse(false);

		if (Pressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		gp->setReverse(true);
		if (Pressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	gp->setVx(speed);

	gp->addVy(translateY);

	if (gp->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void FallState::onCollision(::SidesCollision side)
{
	switch (side)
	{
	case SidesCollision::Left: case SidesCollision::Right:
	{
		gp->setState(new SlipDownState(gp));
		break;
	}
	case SidesCollision::Bottom:
	{
		gp->setState(new StandState(gp));
		break;
	}
	default: break;
	}
}

PlayerState FallState::getState()
{
	return PlayerState::Fall;
}
