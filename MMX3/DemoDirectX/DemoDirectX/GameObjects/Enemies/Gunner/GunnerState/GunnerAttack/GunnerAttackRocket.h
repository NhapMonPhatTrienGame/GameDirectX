#ifndef GUNNER_ATTACK_TWICE_H
#define GUNNER_ATTACK_TWICE_H
#include "../GunnerState.h"

class GunnerAttackRocket :public GunnerState
{
public:
	explicit GunnerAttackRocket(Gunner* pGunner);
	~GunnerAttackRocket() = default;
	::StateGunner getState() override;
	void update(float dt) override;
};
#endif