#ifndef __DASH_STATE_H__
#define __DASH_STATE_H__
#include "../GameState.h"

class DashState : public GameState
{
protected:
	float translateX;
	float timePress;

public:
	explicit DashState(GamePlayer* gp);
	~DashState() = default;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(::SidesCollision side) override;

	PlayerState getState() override;


};
#endif