#pragma once
#include "../GameState.h"

class JumpState : public GameState
{
protected:

	float translateY;
	bool Pressed;
	float countPress;
public:
	explicit JumpState(GamePlayer* gp);
	~JumpState() = default;

	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};
