#include "JumpState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlipDownState/SlipDownState.h"
#include "../../../../GameDefines/GameDefine.h"

JumpState::JumpState(GamePlayer* gp) : GameState(gp)
{
	this->gp->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	translateY = 15.0f;
	timePress = 0;
	Pressed = false;
	if (gp->getState() == PlayerState::Dash)
		Pressed = true;
}

void JumpState::update(float dt)
{
	if (gp->getVy() > 0)
		gp->setState(new FallState(gp, Pressed));
}

void JumpState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	timePress += dt; //tranhs loi va cham
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
}

void JumpState::onCollision(SidesCollision side)
{
	switch (side)
	{
	case SidesCollision::Left: case SidesCollision::Right:
	{
		if (timePress < 0.3f)
			break;
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

PlayerState JumpState::getState()
{
	return PlayerState::Jump;
}
