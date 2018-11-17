#include "EnemiesState.h"


EnemiesState::EnemiesState(Enemies* e)
{
	this->e = e;
}

void EnemiesState::onCollision(Entity::SideCollisions side)
{
}

void EnemiesState::update(float dt)
{
}
