#include "EnemiesJumpState.h"
#include "Enemies.h"
#include "EnemiesStandState.h"
#include "EnemiesFallState.h"

EnemiesJumpState::EnemiesJumpState(Enemies* e) :EnemiesState(e)
{
	e->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	if (e->getFlip())
		e->setVx(200);
	else
		e->setVx(-200);

	translateY = 15.0f;
}

EnemyState::EnemyStateName EnemiesJumpState::getState()
{
	return EnemyState::Jump;
}

void EnemiesJumpState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Left:
	case Entity::Right:
		break;
	case Entity::Bottom:
		break;
	case Entity::Top:
		e->setState(new EnemiesFallState(e));
		break;
	default: break;
	}
}

void EnemiesJumpState::update(float dt)
{
	e->addVy(translateY);
	if (e->getVy() > 0)
	{
		e->setState(new EnemiesFallState(e));
	}
}