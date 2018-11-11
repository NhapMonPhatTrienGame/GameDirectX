#ifndef __APPEAR_STATE_H__
#define __APPEAR_STATE_H__
#include "../GameState.h"

class AppearState :public GameState
{
	float translateY;
public:
	AppearState();
	explicit AppearState(GamePlayer *gp);
	~AppearState() override;
	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};

#endif
