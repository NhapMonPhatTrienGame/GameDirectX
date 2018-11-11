#pragma once
#include "../GameState.h"

class FallState : public GameState
{
	float acceleratorY;
	float acceleratorX;
	bool Pressed;
	//First Velocity equal zero in case speed won't decrease 
	bool allowMoveX;

	bool isLeftOrRightKeyPressed;
public:
	explicit FallState(GamePlayer *gp, bool dash = false);
	FallState();
	~FallState() override;

	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};
