#pragma once
#include "../../GameState.h"

class SlideHorizontalState : public GameState
{
protected:
	float translateX;
	float m_TimePress;

public:
	explicit SlideHorizontalState(GamePlayer* gp);
	~SlideHorizontalState() = default;

	void HandleKeyboard(std::map<int, bool> keys, float dt) override;

	void OnCollision(Entity::SideCollisions side) override;

	MegaManState::StateName getState() override;
};
