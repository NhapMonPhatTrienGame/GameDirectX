#include "AppearState.h"
#include "../../GamePlayer.h"
#include "../StandState/StandState.h"

AppearState::AppearState(GamePlayer* gp) : GameState(gp)
{
	translateY = 25.0f;
}

void AppearState::Update(float dt)
{
	if (gp->getAnimation()->getCurrentColumn() == 0)
		gp->getAnimation()->setPause(true);

	else if (gp->getAnimation()->getCurrentColumn() >= 4)
		gp->setState(new StandState(gp));
}

void AppearState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	gp->addVy(translateY);

	if (gp->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::OnCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Bottom:
	{
		gp->getAnimation()->setPause(false);
		break;
	}
	default: break;
	}
}

StateName AppearState::getState()
{
	return Appear;
}
