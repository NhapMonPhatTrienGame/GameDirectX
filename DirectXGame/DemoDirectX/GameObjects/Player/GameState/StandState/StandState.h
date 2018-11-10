#pragma once
#include "../GameState.h"

class StandState : public GameState
{
public:
	StandState();
	explicit StandState(GamePlayer *gp);
	~StandState() override;

	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys) override;
	MegaManState::StateName getState() override;
	void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) override;
};
