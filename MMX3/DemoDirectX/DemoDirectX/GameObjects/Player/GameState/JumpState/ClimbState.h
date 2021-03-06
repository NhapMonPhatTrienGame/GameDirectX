#ifndef __CLIMB_STATE_H__
#define __CLIMB_STATE_H__
#include "../GameState.h"


class ClimbState : public GameState
{
public:
	explicit ClimbState(GamePlayer* gp) :GameState(gp) {}
	~ClimbState() = default;

	PlayerState getState() override;
};

#endif