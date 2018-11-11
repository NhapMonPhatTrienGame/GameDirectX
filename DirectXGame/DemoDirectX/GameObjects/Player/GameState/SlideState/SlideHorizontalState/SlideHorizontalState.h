#pragma once
#include "../../GameState.h"

class SlideHorizontalState : public GameState
{
	float translateX;
	float countPress;

public:
	SlideHorizontalState();
	explicit SlideHorizontalState(GamePlayer *gp);
	~SlideHorizontalState() override;
	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};
