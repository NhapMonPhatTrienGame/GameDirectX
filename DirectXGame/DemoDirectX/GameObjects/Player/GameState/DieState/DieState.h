#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__
#include "../GameState.h"


class DieState :public GameState
{
public:
	explicit DieState(GamePlayer *gp);
	~DieState() override = default;

	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};

#endif
