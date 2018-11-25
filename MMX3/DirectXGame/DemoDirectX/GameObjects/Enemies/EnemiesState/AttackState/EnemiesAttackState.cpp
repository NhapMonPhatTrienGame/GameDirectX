#include "EnemiesAttackState.h"
#include "../JumpState/EnemiesJumpState.h"

EnemiesAttackState::EnemiesAttackState(Enemies* e) : EnemiesState(e)
{
	timeAttack = 0.0f;
	count = 0;
}

void EnemiesAttackState::update(float dt)
{
	timeAttack += dt;

	if(timeAttack > 1.0f)
	{
		timeAttack = 0.0f;
		count++;

		if (count > 3)
		{
			e->setState(new EnemiesJumpState(e));
			return;
		}

		auto* eBullet = new EnemiesBullet();

		float posX = 0.0f;
		float posY = e->getBound().top + eBullet->getHeight();
		eBullet->setVy(-400);

		if (e->getFlip())
		{
			posX = e->getBound().right - eBullet->getWidth();
			eBullet->setPosition(posX, posY);
			eBullet->setVx(80);
		}
		else
		{
			posX = e->getBound().left + eBullet->getWidth();
			eBullet->setPosition(posX, posY);
			eBullet->setVx(-80);
		}

		if (e->getBullet()->size() <= 3)
			e->getBullet()->push_back(eBullet);
		else
			e->getBullet()->at(count) = eBullet;
	}
}

Enemies::StateName EnemiesAttackState::getState()
{
	return Enemies::StateName::Attack;
}
