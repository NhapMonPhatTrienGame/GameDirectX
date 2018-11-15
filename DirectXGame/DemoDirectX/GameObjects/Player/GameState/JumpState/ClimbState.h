#ifndef __CLIMB_STATE_H__
#define __CLIMB_STATE_H__
#include "../GameState.h"


class ClimbState :public GameState
{
public:
	explicit ClimbState(GamePlayer *gp);
	~ClimbState() override = default;

	void Update(float dt) override;

	void HandleKeyboard(std::map<int, bool> keys, float dt) override;

	void OnCollision(Entity::SideCollisions side) override;

	MegaManState::StateName getState() override;
};

#endif
