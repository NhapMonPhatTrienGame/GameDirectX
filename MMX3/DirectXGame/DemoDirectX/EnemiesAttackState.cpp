#include "EnemiesAttackState.h"
#include "Enemies.h"
#include "EnemiesJumpState.h"

EnemiesAttackState::EnemiesAttackState(Enemies* e) : EnemiesState(e)
{
	//chỗ này lỗi game nên tạo 1 class đạn e rồi new xong add vào list đạn e
	//pShooter = new Sprite("Resources/Enemies/EnemiesShooter.png");
	//pShooter->setPosition(pShooter->getWidth() - e->getWidth(), e->getHeight() / 4.0f);
	//pShooter->drawSprite(pShooter->getPosition());
	timeAttack = 0.0f;
}

EnemiesAttackState::~EnemiesAttackState()
{
	SAFE_DELETE(pShooter);
}

EnemyState::EnemyStateName EnemiesAttackState::getState()
{
	return EnemyState::Attack;
}

void EnemiesAttackState::update(float dt)
{
	timeAttack += dt;
	if(timeAttack > 1.0f)
	{
		e->setState(new EnemiesJumpState(e));
	}
}