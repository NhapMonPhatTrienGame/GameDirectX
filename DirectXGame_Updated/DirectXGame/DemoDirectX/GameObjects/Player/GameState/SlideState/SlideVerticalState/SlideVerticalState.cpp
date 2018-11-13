#include "SlideVerticalState.h"
#include "../../../GamePlayer.h"
#include "../../FallState/FallState.h"
#include "../../StandState/StandState.h"

SlideVerticalState::SlideVerticalState(GamePlayer* gp) :GameState(gp) 
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY/4);
	isSlide = true;
}

void SlideVerticalState::Update(float dt) 
{
	if (!isSlide)
		gp->setState(new FallState(gp));

	isSlide = false;
}

void SlideVerticalState::HandleKeyboard(std::map<int, bool> keys, float dt) 
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY/4);
	if (keys[VK_RIGHT])
	{
		gp->SetReverse(false);
		gp->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		gp->SetReverse(true);
		gp->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		gp->setVx(0);
		gp->setState(new FallState(gp));
	}
}

void SlideVerticalState::OnCollision(Entity::SideCollisions side) 
{
	switch (side)
	{
		case Entity::Left:
		case Entity::Right:
		{
			isSlide = true;
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

MegaManState::StateName SlideVerticalState::getState()
{
	return MegaManState::SlideVertical;
}
