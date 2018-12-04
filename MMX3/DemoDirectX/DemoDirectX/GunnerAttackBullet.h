#pragma once
#include "GameObjects/Enemies/Gunner/GunnerState/GunnerState.h"

class GunnerAttackBullet :
	public GunnerState
{
public:
	explicit GunnerAttackBullet(Gunner* pGunner);
	~GunnerAttackBullet() = default;
	::StateGunner getState() override;
	void update(float dt) override;
};