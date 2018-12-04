#ifndef __JUMP_STATE_H__
#define __JUMP_STATE_H__
#include "../GameState.h"

class JumpState : public GameState
{
protected:

	float translateY;
	bool Pressed;
	float timePress;

public:
	explicit JumpState(GamePlayer* gp);
	~JumpState() = default;

	void update(float dt) override;
	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;
	void onCollision(SidesCollision side) override;
	PlayerState getState() override;
};
#endif