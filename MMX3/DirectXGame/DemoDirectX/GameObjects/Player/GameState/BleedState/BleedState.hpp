#ifndef __BLEED_STATE_H__
#define __BLEED_STATE_H__
#include "../GameState.h"


class BleedState : public GameState
{
public:
	explicit BleedState(GamePlayer* gp) :GameState(gp) {}
	~BleedState() = default;

	void onCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};

#endif
