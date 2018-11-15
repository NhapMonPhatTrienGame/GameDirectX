#include "RunState.h"
#include "../StandState/StandState.h"
#include "../../GamePlayer.h"


RunState::RunState(GamePlayer* gp) : GameState(gp)
{
}

void RunState::Update(float dt) { }

void RunState::HandleKeyboard(std::map<int, bool> keys, float dt)
{
	gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
	if (keys[VK_RIGHT])
	{
		gp->SetReverse(false);
		gp->setVx(Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else if (keys[VK_LEFT])
	{		
		gp->SetReverse(true);
		gp->setVx(-Define::PLAYER_MAX_RUNNING_SPEED);
	}
	else
	{
		gp->setVx(0);
		gp->setState(new StandState(gp));
	}
		
}

StateName RunState::getState()
{
	return Running;
}

void RunState::OnCollision(Entity::SideCollisions side)
{
	switch (side)
	{
		case Entity::Left:
		case Entity::Right:
		{
			//gp->setState(new StandState(gp));
			gp->setPosition(gp->getPosition());
			break;
		}
		default:break;
	}
}