#include "ClingState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlideState/SlideVerticalState/SlideVerticalState.h"
#include "../../GamePlayer.h"

ClingState::ClingState(GamePlayer* gp, bool dash) : GameState(gp)
{
	speed = 0.0f;
	countPress = 0;
	this->gp->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	translateY = 15.0f;

	Pressed = dash;
}


void ClingState::Update(float dt)
{
	if (gp->getVy() > 0)
		gp->setState(new FallState(gp, Pressed));
}

void ClingState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	countPress += dt;
	if (countPress < 0.3f)
	{
		if (gp->getReverse())
		{
			speed = Define::PLAYER_MAX_CLIING_SPEED;
			gp->UpdateColision(1.5, Entity::Left, dt);

			if (keys[VK_RIGHT])
				countPress = 0.3;
		}
		else
		{
			speed = -Define::PLAYER_MAX_CLIING_SPEED;
			gp->UpdateColision(1.5, Entity::Right, dt);

			if (keys[VK_LEFT])
				countPress = 0.3;
		}
		gp->setVx(speed);
		gp->addVy(translateY);
		return;
	}

	if (keys[VK_RIGHT])
	{
		gp->SetReverse(false);

		if (Pressed)
			speed = Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = Define::PLAYER_MAX_RUNNING_SPEED;
	}
	else if (keys[VK_LEFT])
	{
		gp->SetReverse(true);
		if (Pressed)
			speed = -Define::PLAYER_MAX_SLIDE_SPEED;
		else
			speed = -Define::PLAYER_MAX_RUNNING_SPEED;
	}
	gp->setVx(speed);
	gp->addVy(translateY);
}

void ClingState::OnCollision(Entity::SideCollisions side)
{
	switch (side)
	{
		case Entity::Left:
		case Entity::Right:
		{
			gp->setState(new SlideVerticalState(gp));
			break;
		}
		case Entity::Top:
		{
			gp->setState(new FallState(gp, Pressed));
			break;
		}
		case Entity::Bottom:
		{
			gp->setState(new StandState(gp));
			break;
		}
		default: break;
	}
}

StateName ClingState::getState()
{
	return Cling;
}
