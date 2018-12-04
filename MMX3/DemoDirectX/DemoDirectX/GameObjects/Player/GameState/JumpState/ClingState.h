#ifndef __CLING_STATE_H__
#define __CLING_STATE_H__
#include "../GameState.h"

class ClingState : public GameState
{
protected:

	float translateY;
	float speed, countPress;
	bool Pressed;


public:
	explicit ClingState(GamePlayer* gp, bool dash = false);
	~ClingState() = default;

	void update(float dt) override;
	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;
	void onCollision(SidesCollision side) override;
	PlayerState getState() override;
};
#endif