#pragma once
#include "../GameState.h"

class GamePlayer;

class RunState : public GameState
{
protected:
	bool boot;
public:
	explicit RunState(GamePlayer* gp) :GameState(gp) {}
	~RunState() = default;

	void HandleKeyboard(std::map<int, bool> keys, float dt) override;

	MegaManState::StateName getState() override;

	void OnCollision(Entity::SideCollisions side) override;

};
