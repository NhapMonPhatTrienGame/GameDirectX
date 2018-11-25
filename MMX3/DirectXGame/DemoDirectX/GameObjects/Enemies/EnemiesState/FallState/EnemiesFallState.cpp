#include "EnemiesFallState.h"
#include "../StandState/EnemiesStandState.h"
#include "../../../../GameDefines/GameDefine.h"

EnemiesFallState::EnemiesFallState(Enemies * e) :EnemiesState(e)
{
	translateY = 25.0f;
	e->setVy(0);
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

Enemies::StateName EnemiesFallState::getState()
{
	return Enemies::StateName::Fall;
}
