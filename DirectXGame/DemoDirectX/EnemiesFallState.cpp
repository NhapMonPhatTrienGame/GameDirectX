#include "EnemiesFallState.h"
#include "Enemies.h"
#include "EnemiesStandState.h"

EnemiesFallState::EnemiesFallState(Enemies * e) :EnemiesState(e)
{
	translateY = 25.0f;
	e->setVy(0);
}

EnemyState::EnemyStateName EnemiesFallState::getState()
{
	return EnemyState::Fall;
}

void EnemiesFallState::onCollision(Entity::SideCollisions side)
{
	if (side == Entity::Bottom)
		e->setState(new EnemiesStandState(e));
}

void EnemiesFallState::update(float dt)
{
	e->addVy(translateY);
	if (e->getVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		e->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}
