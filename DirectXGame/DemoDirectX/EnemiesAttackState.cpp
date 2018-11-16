#include "EnemiesAttackState.h"
#include "Enemies.h"

EnemiesAttackState::EnemiesAttackState(Enemies* e) : EnemiesState(e)
{
	m_Shooter = new Sprite("Resources/Enemies/EnemiesShooter.png");
	m_Shooter->setPosition(m_Shooter->getWidth() - e->getWidth(), e->getHeight() / 4.0f);
}

EnemiesAttackState::~EnemiesAttackState()
{
	SAFE_DELETE(m_Shooter);
}

EnemyState::EnemyStateName EnemiesAttackState::getState()
{
	return EnemyState::Attack;
}
