#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../GamePlayer.h"


StandState::StandState(GamePlayer* gp) : GameState(gp)
{
	this->gp->setVx(0);
}

void StandState::Update(float dt) 
{

}

void StandState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	if (keys[VK_LEFT] || keys[VK_RIGHT])
		gp->setState(new RunState(gp));

}

StateName StandState::getState()
{
	return Standing;
}

void StandState::OnCollision(Entity::SideCollisions side)
{
	switch (side)
	{
		default:break;
	}
}
