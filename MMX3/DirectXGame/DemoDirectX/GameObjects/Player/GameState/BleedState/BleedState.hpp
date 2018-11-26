#ifndef __BLEED_STATE_H__
#define __BLEED_STATE_H__
#include "../GameState.h"


class BleedState : public GameState
{
public:
	explicit BleedState(GamePlayer* gp, int Direction);
	~BleedState() = default;

	void update(float dt) override;
	GamePlayer::StateName getState() override;

protected:
	float timeBleed;

};

#endif
