#include "StandState.h"
#include "../RunState/RunState.h"
#include "../../GamePlayer.h"

StandState::StandState() {}

StandState::~StandState() {}

StandState::StandState(GamePlayer* gp) : GameState(gp)
{
	this->gp->setVx(0);
	this->gp->setVy(0);
}

void StandState::Update(float dt) {}

void StandState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	if (keys[VK_LEFT] || keys[VK_RIGHT])
		gp->setState(new RunState(gp));
}

StateName StandState::getState()
{
	return Standing;
}

void StandState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) {}
