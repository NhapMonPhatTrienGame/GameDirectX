#pragma once
#include "../GameState.h"

class GamePlayer;

class RunState : public GameState
{
	float accelerationX;
public:
	RunState();
	explicit RunState(GamePlayer *gp);

	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	MegaManState::StateName getState() override;
	void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) override;
	~RunState() override;
};
