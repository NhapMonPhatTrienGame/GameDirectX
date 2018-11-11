#include "AppearState.h"
#include "../../GamePlayer.h"
#include "../StandState/StandState.h"

AppearState::AppearState() {}
AppearState::AppearState(GamePlayer* gp) : GameState(gp)
{
	translateY = 25.0f;
}
AppearState::~AppearState() {}

void AppearState::Update(float dt)
{
	gp->addVy(translateY);

	if (gp->getVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
		gp->setVy(Define::PLAYER_MAX_JUMP_VELOCITY);
}

void AppearState::HandleKeyboard(std::map<int, bool> keys, float dt) {}

void AppearState::OnCollision(Entity::CollisionReturn data, Entity::SideCollisions side)
{
	switch (side)
	{
		case Entity::Left:
		{
			if (gp->getMoveDirection() == GamePlayer::MoveToLeft)
			{
				gp->addPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
				gp->setVx(0);
			}
			break;
		}
		case Entity::Right:
		{
			if (gp->getMoveDirection() == GamePlayer::MoveToRight)
			{
				gp->addPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
				gp->setVx(0);
			}
			break;
		}

		case Entity::Bottom:
		case Entity::BottomRight:
		case Entity::BottomLeft:
		{
			if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
			{
				gp->addPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
				gp->setState(new StandState(gp));
			}
			break;
		}
		default: break;
	}
}

MegaManState::StateName AppearState::getState()
{
	return MegaManState::Appear;
}
