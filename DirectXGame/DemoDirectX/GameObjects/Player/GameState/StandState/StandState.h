#pragma once
#include "../GameState.h"

class StandState : public GameState
{
public:
	explicit StandState(GamePlayer* gp);
	~StandState() = default;

	void HandleKeyboard(std::map<int, bool> keys, float dt) override;

	MegaManState::StateName getState() override;
};
