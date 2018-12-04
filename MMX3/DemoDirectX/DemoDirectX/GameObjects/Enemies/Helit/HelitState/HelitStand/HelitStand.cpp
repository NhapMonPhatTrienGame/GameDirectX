#include "HelitStand.h"
#include "../HelitAttack/HelitAttack.h"

HelitStand::HelitStand(Helit* helit) :HelitState(helit)
{
	helit->setVx(0);
	helit->setVy(0);
	timeAttack = 0;
}

::StateHelit HelitStand::getState()
{
	return StateHelit::Stand;
}

void HelitStand::update(float dt)
{
	timeAttack += dt;
	if(timeAttack > 1.0f)
		helit->setState(new HelitAttack(helit));
}
