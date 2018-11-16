#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__
#include "../GameState.h"


class DieState : public GameState
{
public:
	explicit DieState(GamePlayer* gp) :GameState(gp) {}
	~DieState() = default;

	void Update(float dt) override;
	MegaManState::StateName getState() override;
};

#endif
