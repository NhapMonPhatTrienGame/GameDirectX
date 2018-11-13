#include "FinishState.h"

FinishState::FinishState(GamePlayer* gp) :GameState(gp) {}

void FinishState::Update(float dt) {}

void FinishState::HandleKeyboard(std::map<int, bool> keys, float dt) {}

void FinishState::OnCollision(Entity::SideCollisions side) {}

MegaManState::StateName FinishState::getState()
{
	return MegaManState::Win;
}
