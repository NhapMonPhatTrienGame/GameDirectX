#include "EnemiesAttackState.h"
#include "Enemies.h"

EnemiesAttackState::EnemiesAttackState(Enemies* e) : EnemiesState(e)
{
	pShooter = new Sprite("Resources/Enemies/EnemiesShooter.png");
	pShooter->setPosition(pShooter->getWidth() - e->getWidth(), e->getHeight() / 4.0f);
}

EnemiesAttackState::~EnemiesAttackState()
{
	SAFE_DELETE(pShooter);
}

EnemyState::EnemyStateName EnemiesAttackState::getState()
{
	return EnemyState::Attack;
}
