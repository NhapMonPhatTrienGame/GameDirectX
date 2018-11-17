#pragma once
#include <map>
#include "../../../GameDefines/GameDefine.h"
#include "../../Entity/Entity.h"


class GamePlayer;

class GameState
{
protected:
	GamePlayer* gp;

public:
	virtual ~GameState() = default;
	explicit GameState(GamePlayer* gp);

	virtual void update(float dt);

	virtual void handlerKeyBoard(std::map<int, bool> keys, float dt);

	// The side will collide with player
	virtual void onCollision(Entity::SideCollisions side);

	virtual MegaManState::StateName getState() = 0;
};
