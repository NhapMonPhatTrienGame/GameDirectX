#pragma once
#include "../GameState.h"

class ClimbState : public GameState
{
protected:
	float acceleratorY;
	float speed, countPress;
	bool Pressed;
public:
	explicit ClimbState(GamePlayer *gp, bool dash = false);
	ClimbState();
	~ClimbState() override;


	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};