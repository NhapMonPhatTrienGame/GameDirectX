#include "DieState.h"
#include "../../GamePlayer.h"

DieState::DieState(GamePlayer* gp) :GameState(gp) {}

void DieState::Update(float dt)
{
	gp->GetAnimation()->SetAnimation(20, 3, 0.15, false);
}

void DieState::HandleKeyboard(std::map<int, bool> keys, float dt) {}

void DieState::OnCollision(Entity::SideCollisions side) {}

StateName DieState::getState()
{
	return Die;
}
