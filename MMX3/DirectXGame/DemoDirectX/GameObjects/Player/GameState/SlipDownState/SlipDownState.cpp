#include "SlipDownState.h"
#include "../StandState/StandState.h"
#include "../FallState/FallState.h"
#include "../../GamePlayer.h"

SlipDownState::SlipDownState(GamePlayer* gp) : GameState(gp)
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	isSlide = true;
}

void SlipDownState::update(float dt)
{
	if (!isSlide)
		gp->setState(new FallState(gp));

	isSlide = false;
}

void SlipDownState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY / 4);
	if (keys[VK_RIGHT])
	{
		gp->setReverse(false);
		gp->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{
		gp->setReverse(true);
		gp->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		gp->setVx(0);
		gp->setState(new FallState(gp));
	}
}

void SlipDownState::onCollision(Entity::SideCollisions side)
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

MegaManState::StateName SlipDownState::getState()
{
	return MegaManState::SlipDown;
}
