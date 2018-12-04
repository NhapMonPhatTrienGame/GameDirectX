#include "AppearState.h"
#include "../StandState/StandState.h"
#include "../../../../GameDefines/GameDefine.h"

AppearState::AppearState(GamePlayer* gp) : GameState(gp)
{
	translateY = 25.0f;
}

void AppearState::update(float dt)
{
	if (gp->getAnimation()->getCurrentColumn() == 0)
		gp->getAnimation()->setPause(true);

	else if (gp->getAnimation()->getCurrentColumn() >= 4)
		gp->setState(new StandState(gp));
}

void AppearState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	gp->addVy(translateY);

	if (gp->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::onCollision(::SidesCollision side)
{
	switch (side)
	{
	case SidesCollision::Bottom:
	{
		gp->getAnimation()->setPause(false);
		break;
	}
	default: break;
	}
}

PlayerState AppearState::getState()
{
	return PlayerState::Appear;
}
