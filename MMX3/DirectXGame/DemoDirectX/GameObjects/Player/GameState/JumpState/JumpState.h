#pragma once
#include "../GameState.h"

class JumpState : public GameState
{
protected:

	float translateY;
	bool Pressed;
	float timePress;
public:
	explicit JumpState(GamePlayer* gp);
	~JumpState() = default;

	void update(float dt) override;
	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;
	void onCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};
