#include "HelitDie.h"
#include "../../../../../GameDefines/GameDefine.h"

HelitDie::HelitDie(Helit* helit) :HelitState(helit)
{
    helit->setVy(Define::ENEMY_MIN_JUMP_VELOCITY);
    timeDie = 0;
    translateY = 25.0f;
}

::StateHelit HelitDie::getState()
{
    return StateHelit::Die;
}

void HelitDie::update(float dt)
{
    helit->addVy(translateY);

    timeDie += dt;
    if (timeDie >= 0.45f)
    {
        helit->setDraw(false);
    }
}
