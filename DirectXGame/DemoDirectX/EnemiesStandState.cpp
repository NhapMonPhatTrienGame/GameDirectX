#include "EnemiesStandState.h"
#include "Enemies.h"
#include "EnemiesJumpState.h"
#include "EnemiesAttackState.h"

EnemiesStandState::EnemiesStandState(Enemies* e) : EnemiesState(e)
{
	e->setVx(0);
	e->setVy(0);
	timeJump = 0.0f;
}

EnemyState::EnemyStateName EnemiesStandState::getState()
{
	return EnemyState::Stand;
}

void EnemiesStandState::update(float dt)
{
	timeJump += dt;
	e->setState(new EnemiesAttackState(e));
	if (timeJump > 0.3f)
		e->setState(new EnemiesJumpState(e));
}