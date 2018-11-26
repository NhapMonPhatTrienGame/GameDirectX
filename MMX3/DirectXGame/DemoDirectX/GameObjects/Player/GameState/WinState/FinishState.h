#ifndef __FINISH_STATE_H__
#define __FINISH_STATE_H__
#include "../GameState.h"

class FinishState : public GameState
{
public:
	explicit FinishState(GamePlayer* gp) :GameState(gp) {}
	~FinishState() = default;
	GamePlayer::StateName getState() override;
};

#endif
