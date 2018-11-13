#ifndef __FINISH_STATE_H__
#define __FINISH_STATE_H__
#include "../GameState.h"

class FinishState :public GameState
{
public:
	explicit FinishState(GamePlayer *gp);
	~FinishState() override = default;

	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};

#endif
