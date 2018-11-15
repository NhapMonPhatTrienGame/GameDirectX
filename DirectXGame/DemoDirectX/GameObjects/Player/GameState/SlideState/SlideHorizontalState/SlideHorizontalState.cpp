#include "SlideHorizontalState.h"
#include "../../../GamePlayer.h"
#include "../../StandState/StandState.h"
#include <iostream>

SlideHorizontalState::SlideHorizontalState(GamePlayer* gp) : GameState(gp)
{
	translateX = 25.0f;
	countPress = 0;
}

void SlideHorizontalState::Update(float dt) {}

void SlideHorizontalState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	countPress += dt;
	if (countPress <= 0.45f)
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

void SlideHorizontalState::OnCollision(Entity::SideCollisions side)
{
	switch (side)
	{
		case Entity::Left:
		case Entity::Right:
		{
			gp->setState(new StandState(gp));
			break;
		}
		default:break;
	}

}

StateName SlideHorizontalState::getState()
{
	return SlideHorizontal;
}
