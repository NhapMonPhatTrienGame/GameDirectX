#include "ClimbState.h"
ClimbState::ClimbState(GamePlayer* gp):GameState(gp) {}

void ClimbState::Update(float dt) {}

void ClimbState::HandleKeyboard(std::map<int, bool> keys, float dt) {}

void ClimbState::OnCollision(Entity::SideCollisions side) {}

MegaManState::StateName ClimbState::getState()
{
	return MegaManState::Climb;
}
