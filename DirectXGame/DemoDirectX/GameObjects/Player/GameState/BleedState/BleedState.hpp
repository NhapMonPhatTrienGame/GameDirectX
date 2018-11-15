#ifndef __BLEED_STATE_H__
#define __BLEED_STATE_H__
#include "../GameState.h"


class BleedState :public GameState
{
public:
	explicit BleedState(GamePlayer *gp);
	~BleedState() = default;

	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};

#endif
