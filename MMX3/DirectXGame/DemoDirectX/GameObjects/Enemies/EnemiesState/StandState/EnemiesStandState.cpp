#include "EnemiesStandState.h"
#include "../../../../GameDefines/GameDefine.h"
#include "../AttackState/EnemiesAttackState.h"

EnemiesStandState::EnemiesStandState(Enemies* e) : EnemiesState(e)
{
	e->setVx(0);
	e->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
	timePerShoot = 0.0f;
}


Enemies::StateName EnemiesStandState::getState()
{
	return Enemies::StateName::Stand;
}

void EnemiesStandState::update(float dt)
{
	timePerShoot += dt;
	if (timePerShoot > 1.0f)
	{
		e->setState(new EnemiesAttackState(e));
	}
}
