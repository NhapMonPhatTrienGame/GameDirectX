#pragma once
#include "../../GameState.h"

class SlideVerticalState : public GameState
{
protected:
		bool isSlide;
public:
	SlideVerticalState();
	explicit SlideVerticalState(GamePlayer *gp);
	~SlideVerticalState() override;
	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};
