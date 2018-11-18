#include "BleedState.hpp"
#include "../../GamePlayer.h"
#include "../DieState/DieState.h"


void BleedState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Left: case Entity::Right: case Entity::Top: case Entity::Bottom: case Entity::TopLeft:
	case Entity::TopRight: case Entity::BottomLeft: case Entity::BottomRight:
	{
		if (gp->Tag == Entity::Enemy)
		{
			gp->addHP(-1.0f);
			gp->getAnimation()->setAnimation(19, 2, 0.15, false);
		}
		if (gp->getHP() <= 0)
			gp->setState(new DieState(gp));
		break;
	}
	default: break;
	}
}

StateName BleedState::getState()
{
	return Bleed;
}
