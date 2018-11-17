#pragma once
#include "../GameState.h"

class DashState : public GameState
{
protected:
	float translateX;
	float m_TimePress;

public:
	explicit DashState(GamePlayer* gp);
	~DashState() = default;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(Entity::SideCollisions side) override;

	MegaManState::StateName getState() override;
};
