#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__
#include "../GameState.h"


class DieState : public GameState
{
public:
	explicit DieState(GamePlayer* gp);
	~DieState() = default;

	void update(float dt) override;
	GamePlayer::StateName getState() override;

protected:
	float timeDie;

};

#endif
