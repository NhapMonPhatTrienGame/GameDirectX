#include "ClingState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"

ClingState::ClingState(GamePlayer* gp, bool dash) : GameState(gp)
{
	speed = 0.0f;
	countPress = 0;
	this->gp->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	translateY = 15.0f;

	Pressed = dash;
}


void ClingState::update(float dt)
{
	if (gp->getVy() > 0)
		gp->setState(new FallState(gp, Pressed));
}

void ClingState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	countPress += dt;
	if (countPress < 0.3f)
	{
		if (gp->getReverse())
		{
			speed = Define::PLAYER_MAX_CLING_SPEED;
			
			if (keys[VK_RIGHT])
				countPress = 0.3;
		}
		else
		{
			speed = -Define::PLAYER_MAX_CLING_SPEED;

			if (keys[VK_LEFT])
				countPress = 0.3;
		}
		gp->setVx(speed);
		gp->addVy(translateY);
		return;
	}

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
}

void ClingState::onCollision(::SidesCollision side)
{
	switch (side)
	{
	case SidesCollision::Left: case SidesCollision::Right:
	{
		gp->setState(new SlipDownState(gp));
		break;
	}
	case SidesCollision::Top:
	{
		gp->setState(new FallState(gp, Pressed));
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

PlayerState ClingState::getState()
{
	return PlayerState::Cling;
}
