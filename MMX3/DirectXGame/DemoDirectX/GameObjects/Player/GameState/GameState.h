#pragma once
#include <map>
#include "../../Entity/Entity.h"
#include "../GamePlayer.h"

class GamePlayer;

class GameState
{
public:
	virtual ~GameState() = default;
	explicit GameState(GamePlayer* gp);

	virtual void update(float dt);

	virtual void handlerKeyBoard(std::map<int, bool> keys, float dt);

	// The side will collide with player
	virtual void onCollision(Entity::SideCollisions side);

	virtual GamePlayer::StateName getState() = 0;

protected:
	GamePlayer* gp;

};
