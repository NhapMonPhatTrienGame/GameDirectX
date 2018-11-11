#include "SlideVerticalState.h"


SlideVerticalState::SlideVerticalState(GamePlayer* gp) :GameState(gp) {}
SlideVerticalState::SlideVerticalState() {}
SlideVerticalState::~SlideVerticalState() {}

void SlideVerticalState::Update(float dt) {}

void SlideVerticalState::HandleKeyboard(std::map<int, bool> keys, float dt) {}

void SlideVerticalState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) {}

MegaManState::StateName SlideVerticalState::getState()
{
	return MegaManState::SlideVertical;
}
