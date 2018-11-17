#include "EnemiesJumpState.h"
#include "Enemies.h"
#include "EnemiesStandState.h"
#include "EnemiesFallState.h"

EnemiesJumpState::EnemiesJumpState(Enemies* e) :EnemiesState(e)
{
	e->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	translateY = 15.0f;
	timeJump = 0.0f;
}

EnemyState::EnemyStateName EnemiesJumpState::getState()
{
	return EnemyState::Jump;
}

void EnemiesJumpState::onCollision(Entity::SideCollisions side)
{
	switch (side)
	{
	case Entity::Left:case Entity::Right:case Entity::Top:
		e->setState(new EnemiesFallState(e));
		break;
	case Entity::Bottom:
		e->setState(new EnemiesStandState(e));
		break;
	default: break;
	}
}

void EnemiesJumpState::update(float dt)
{
	timeJump += dt;
	if (timeJump > 0.3f)
	{
		if (!e->getFlip())
			e->setVx(300.0f);
		else
			e->setVx(-300.0f);
	}
	e->addVy(translateY);
	if (e->getVy() > 0)
		e->setState(new EnemiesFallState(e));
}