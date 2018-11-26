#ifndef __FALL_STATE_H__
#define __FALL_STATE_H__
#include "../GameState.h"

class FallState : public GameState
{
public:
	explicit FallState(GamePlayer* gp, bool dash = false);
	~FallState() = default;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(Entity::SideCollisions side) override;

	GamePlayer::StateName getState() override;

protected:

	float translateY;
	float translateX;
	bool Pressed;
	//First Velocity equal zero in case speed won't decrease 
	bool allowMoveX;

	bool isLeftOrRightKeyPressed;

};
#endif
