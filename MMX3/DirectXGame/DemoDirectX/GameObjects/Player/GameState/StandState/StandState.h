#ifndef __STAND_STATE_H__
#define __STAND_STATE_H__
#include "../GameState.h"

class StandState : public GameState
{
public:
	explicit StandState(GamePlayer* gp);
	~StandState() = default;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	GamePlayer::StateName getState() override;
};
#endif