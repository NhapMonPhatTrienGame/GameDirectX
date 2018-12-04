#ifndef __DIE_STATE_H__
#define __DIE_STATE_H__
#include "../GameState.h"


class DieState : public GameState
{
protected:
	float timeDie;


public:
	explicit DieState(GamePlayer* gp);
	~DieState() = default;

	void update(float dt) override;
	PlayerState getState() override;

};

#endif
