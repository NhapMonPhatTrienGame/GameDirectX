#include "EnemiesStandState.h"
#include "Enemies.h"
#include "EnemiesJumpState.h"
#include "EnemiesAttackState.h"

EnemiesStandState::EnemiesStandState(Enemies* e) : EnemiesState(e)
{
	e->setVx(0);
	e->setVy(0);
}

EnemyState::EnemyStateName EnemiesStandState::getState()
{
	return EnemyState::Stand;
}

void EnemiesStandState::Update(float t_GameTime)
{
	m_TimeJump += t_GameTime;

	e->setState(new EnemiesAttackState(e));

	if (m_TimeJump > 0.3f)
		e->setState(new EnemiesJumpState(e));
}
