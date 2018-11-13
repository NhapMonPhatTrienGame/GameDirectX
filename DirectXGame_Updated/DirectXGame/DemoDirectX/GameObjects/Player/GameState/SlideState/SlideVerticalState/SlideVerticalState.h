#ifndef __SLIDE_VERTICAL_STATE_H__
#define __SLIDE_VERTICAL_STATE_H__

#include "../../GameState.h"

class SlideVerticalState : public GameState
{
protected:
		bool isSlide;
public:
	SlideVerticalState() = default;
	explicit SlideVerticalState(GamePlayer *gp);
	~SlideVerticalState() override = default;

	void Update(float dt) override;

	void HandleKeyboard(std::map<int, bool> keys, float dt) override;

	void OnCollision(Entity::SideCollisions side) override;

	MegaManState::StateName getState() override;
};
#endif