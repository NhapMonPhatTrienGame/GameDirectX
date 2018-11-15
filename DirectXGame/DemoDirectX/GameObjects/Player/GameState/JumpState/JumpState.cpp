#include "JumpState.h"
#include "../FallState/FallState.h"
#include "../StandState/StandState.h"
#include "../SlideState/SlideVerticalState/SlideVerticalState.h"
#include "../../GamePlayer.h"

JumpState::JumpState(GamePlayer* gp) : GameState(gp)
{
	this->gp->setVy(Define::PLAYER_MIN_JUMP_VELOCITY);
	translateY = 15.0f;
	countPress = 0;
	Pressed = false;
	if (gp->getState() == SlideHorizontal)
		Pressed = true;
}

void JumpState::Update(float dt)
{
	if (gp->getVy() > 0)
		gp->setState(new FallState(gp, Pressed));

}

void JumpState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	countPress += dt;//tranhs loi va cham
	float speed = 0.0f;
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

void JumpState::OnCollision(Entity::SideCollisions side)
{
	switch (side)
	{
		case Entity::Left:
		case Entity::Right:
		{
			if (countPress < 0.3f)
				break;
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

StateName JumpState::getState()
{
	return Jumping;
}
