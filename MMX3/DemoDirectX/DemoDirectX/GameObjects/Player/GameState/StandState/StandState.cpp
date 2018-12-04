#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../../../GameDefines/GameDefine.h"


StandState::StandState(GamePlayer* gp) : GameState(gp)
{
	this->gp->setVx(0);
}

void StandState::handlerKeyBoard(std::map<int, bool> keys, float dt)
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	if (keys[VK_LEFT] || keys[VK_RIGHT])
		gp->setState(new RunState(gp));
}

PlayerState StandState::getState()
{
	return PlayerState::Stand;
}
