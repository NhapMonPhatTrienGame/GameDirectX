#include "EnemiesState.h"


EnemiesState::EnemiesState(Enemies* e)
{
	this->e = e;
}

void EnemiesState::OnCollision(Entity::SideCollisions t_Side)
{
}

void EnemiesState::Update(float t_GameTime)
{
}
