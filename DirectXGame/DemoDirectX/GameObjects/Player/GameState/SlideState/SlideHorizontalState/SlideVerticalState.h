#ifndef __SLIDE_VERTICAL_STATE_H__
#define __SLIDE_VERTICAL_STATE_H__
#include "../../GameState.h"

class SlideVerticalState : public GameState
{
public:
	explicit SlideVerticalState(GamePlayer *gp);
	SlideVerticalState();
	~SlideVerticalState() override;
	void Update(float dt) override;
	void HandleKeyboard(std::map<int, bool> keys, float dt) override;
	void OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side) override;
	MegaManState::StateName getState() override;
};

#endif
