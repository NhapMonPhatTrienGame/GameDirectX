#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../GamePlayer.h"
#include "../JumpState/JumpState.h"

RunState::RunState() {}

RunState::RunState(GamePlayer* gp) : GameState(gp)
{
	accelerationX = 25.0f;
	this->gp->allowLeft = true;
	this->gp->allowRight = true;
}

void RunState::Update(float dt) { }

void RunState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	if (keys[VK_RIGHT])
	{
		gp->slideRight = true;
		gp->slideLeft = false;
		if (gp->allowRight)
		{
			gp->SetReverse(false);
			//Move to right
			if (gp->getVx() < Define::PLAYER_MAX_RUNNING_SPEED)
			{
				gp->addVx(accelerationX);
				if (gp->getVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
					gp->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else if (keys[VK_LEFT])
	{
		gp->slideLeft = true;
		gp->slideRight = false;
		if (gp->allowLeft)
		{			
			gp->SetReverse(true);
			//Move to left
			if (gp->getVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
			{
				gp->addVx(-accelerationX);
				if (gp->getVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
					gp->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
			}
		}
	}
	else
		gp->setState(new StandState(gp));
}

StateName RunState::getState()
{
	return Running;
}

void RunState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (side)
	{
		case Entity::Left:
		{
			//Collision left of player side
			if (gp->getMoveDirection() == GamePlayer::MoveToLeft)
			{
				gp->allowLeft = false;
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
				gp->allowRight = false;
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

RunState::~RunState() {}
