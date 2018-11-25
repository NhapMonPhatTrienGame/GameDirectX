#ifndef __RUN_STATE_H__
#define __RUN_STATE_H__
#include "../GameState.h"

class GamePlayer;

class RunState : public GameState
{
public:
	explicit RunState(GamePlayer* gp) :GameState(gp) {}
	~RunState() = default;

	void handlerKeyBoard(std::map<int, bool> keys, float dt) override;

	void onCollision(Entity::SideCollisions side) override;

	GamePlayer::StateName getState() override;

protected:
	bool boot;

};
#endif
