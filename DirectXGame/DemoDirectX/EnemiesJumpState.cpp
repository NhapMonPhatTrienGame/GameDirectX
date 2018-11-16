#include "EnemiesJumpState.h"
#include "Enemies.h"
#include "EnemiesStandState.h"

EnemiesJumpState::EnemiesJumpState(Enemies* e) :EnemiesState(e)
{
	e->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
	m_TranslateY = 15.0f;
	m_TimeJump = 0;
}

EnemyState::EnemyStateName EnemiesJumpState::getState()
{
	return EnemyState::Jump;
}

void EnemiesJumpState::OnCollision(Entity::SideCollisions t_Side)
{
	switch (t_Side)
	{
	case Entity::Left:
		e->setState(new EnemiesStandState(e));
		break;
	case Entity::Right:
		e->setState(new EnemiesStandState(e));
		break;
	case Entity::Top:
		e->addVy(m_TranslateY);
		break;
	case Entity::Bottom:
		e->setState(new EnemiesStandState(e));
		break;
	default: break;
	}
}

void EnemiesJumpState::Update(float t_GameTime)
{
	m_TimeJump += t_GameTime;
	if (m_TimeJump > 0.3f)
	{
		if (!e->getFlip())
			e->setVx(300.0f);
		else
			e->setVx(-300.0f);
	}

	if (e->getVy() > 0)
		e->addVy(m_TranslateY);
	else if (e->getVy() > Define::ENEMY_MAX_JUMP_VELOCITY)
		e->setVy(Define::ENEMY_MAX_JUMP_VELOCITY);
}
