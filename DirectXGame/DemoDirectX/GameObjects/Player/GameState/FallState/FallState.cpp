#include "FallState.h"
#include "../../GamePlayer.h"
#include "../RunState/RunState.h"
#include "../StandState/StandState.h"
#include "../SlideState/SlideHorizontalState/SlideVerticalState.h"

FallState::FallState(GamePlayer* gp) : GameState(gp)
{
	acceleratorY = 15.0f;
	acceleratorX = 8.0f;

	if (this->gp->getVx() == 0)
		allowMoveX = false;
	else
		allowMoveX = true;
}

FallState::FallState() {}
FallState::~FallState() {}

void FallState::Update(float dt)
{
	gp->addVy(acceleratorY);

	if (gp->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void FallState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	if (keys[VK_RIGHT])
	{
		gp->SetReverse(false);

		isLeftOrRightKeyPressed = true;
		//Move to left
		if (gp->getVx() < Define::PLAYER_MAX_RUNNING_SPEED)
		{
			gp->addVx(acceleratorX);

			if (gp->getVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
				gp->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
		}
	}
	else if (keys[VK_LEFT])
	{
		gp->SetReverse(true);

		isLeftOrRightKeyPressed = true;
		//Move to  right
		if (gp->getVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
		{
			gp->addVx(-acceleratorX);

			if (gp->getVx() <= -Define::PLAYER_MAX_RUNNING_SPEED)
				gp->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
		}
	}
	else
		isLeftOrRightKeyPressed = false;
}

void FallState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (side)
	{
		case Entity::Left:
		{
			if (gp->getMoveDirection() == GamePlayer::MoveToLeft)
			{
				gp->addPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				gp->setVx(0);
			}
			break;
		}
		case Entity::Right:
		{
			if (gp->getMoveDirection() == GamePlayer::MoveToRight)
			{
				gp->addPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				gp->setVx(0);
			}
			break;
		}

		case Entity::Bottom:
		case Entity::BottomRight:
		case Entity::BottomLeft:
		{
			if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				gp->addPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

				if (isLeftOrRightKeyPressed)
					gp->setState(new RunState(gp));
				else
					gp->setState(new StandState(gp));
			}
			break;
		}
		default: break;
	}
}

StateName FallState::getState()
{
	return Falling;
}
