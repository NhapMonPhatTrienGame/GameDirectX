#pragma once
#include "../GameState.h"

class FallState : public GameState
{
	float translateY;
	float translateX;
	bool Pressed;
	//First Velocity equal zero in case speed won't decrease 
	bool allowMoveX;

	bool isLeftOrRightKeyPressed;
public:
	explicit FallState(GamePlayer *gp, bool dash = false);
	FallState() = default;
	~FallState() override = default;

	void Update(float dt) override;

	void HandleKeyboard(std::map<int, bool> keys, float dt) override;

	void OnCollision(Entity::SideCollisions side) override;

	MegaManState::StateName getState() override;
};
