#pragma once
#include "../GameState.h"

class JumpState : public GameState
{
	float acceleratorY;
	float acceleratorX;
	bool noPressed;
	bool allowMoveRight, allowMoveLeft;
public:
	explicit JumpState(GamePlayer *gp);
	JumpState();
	~JumpState() override;


	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};
