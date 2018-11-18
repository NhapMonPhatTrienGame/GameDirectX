#include "EnemiesStandState.h"
#include "Enemies.h"
#include "EnemiesJumpState.h"
#include "EnemiesAttackState.h"

EnemiesStandState::EnemiesStandState(Enemies* e) : EnemiesState(e)
{
	e->setVx(0);
	e->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
	timePerShoot = 0.0f;
}

EnemyState::EnemyStateName EnemiesStandState::getState()
{
	return EnemyState::Stand;
}

void EnemiesStandState::update(float dt)
{
	timePerShoot += dt;
	if (timePerShoot > 1.0f)
	{
		e->setState(new EnemiesAttackState(e));
	}
}