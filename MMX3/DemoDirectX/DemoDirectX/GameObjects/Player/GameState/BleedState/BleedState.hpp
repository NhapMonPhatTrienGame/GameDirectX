#ifndef __BLEED_STATE_H__
#define __BLEED_STATE_H__
#include "../GameState.h"


class BleedState : public GameState
{
protected:
	float timeBleed;

public:
	explicit BleedState(GamePlayer* gp, int Direction);
	~BleedState() = default;

	void update(float dt) override;
	PlayerState getState() override;
};

#endif
