#include "SlideHorizontalState.h"
#include "../../../GamePlayer.h"
#include "../../StandState/StandState.h"
#include <iostream>

SlideHorizontalState::SlideHorizontalState() {}
SlideHorizontalState::SlideHorizontalState(GamePlayer* gp) : GameState(gp)
{
	translateX = 25.0f;
	countPress = 0;
}
SlideHorizontalState::~SlideHorizontalState() {}

void SlideHorizontalState::Update(float dt) {}

void SlideHorizontalState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	countPress += dt;
	if (countPress <= 0.45f)
	{
		if (gp->slideRight)
		{
			gp->SetReverse(false);
			if (gp->getVx() < Define::PLAYER_MAX_SLIDE_SPEED)
			{
				gp->addVx(translateX);
				if (gp->getVx() >= Define::PLAYER_MAX_SLIDE_SPEED)
					gp->setVx(Define::PLAYER_MAX_SLIDE_SPEED);
			}
		}
		else if (gp->slideLeft)
		{
			gp->SetReverse(true);
			if (gp->getVx() > -Define::PLAYER_MAX_SLIDE_SPEED)
			{
				gp->addVx(-translateX);
				if (gp->getVx() < -Define::PLAYER_MAX_SLIDE_SPEED)
					gp->setVx(-Define::PLAYER_MAX_SLIDE_SPEED);
			}
		}
	}
	else
		gp->setState(new StandState(gp));
}

void SlideHorizontalState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (side)
	{
		case Entity::Left:
		{
			//Collision left of player side
			if (gp->getMoveDirection() == GamePlayer::MoveToLeft)
			{
				gp->slideLeft = false;
				//Player is pushed right that player not through object
				gp->addPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

				//gp->setState(new StandState(gp));
				gp->setPosition(gp->getPosition());
			}
			break;
		}
		case Entity::Right:
		{
			//Collision right of player side
			if (gp->getMoveDirection() == GamePlayer::MoveToRight)
			{
				gp->slideRight = false;
				gp->addPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				//gp->setState(new StandState(gp));
				gp->setPosition(gp->getPosition());
			}
			break;
		}
		case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
		{
			gp->addPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
			gp->setVy(0);
			break;
		}
		default:break;
	}

}

MegaManState::StateName SlideHorizontalState::getState()
{
	return MegaManState::SlideHorizontal;
}
