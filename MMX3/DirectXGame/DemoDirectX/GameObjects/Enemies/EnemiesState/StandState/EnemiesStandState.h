#pragma once
#include "../EnemiesState.h"


class EnemiesStandState :
	public EnemiesState
{
public:
	explicit EnemiesStandState(Enemies *e);
	~EnemiesStandState() = default;

	Enemies::StateName getState() override;
	void update(float dt) override;

protected:
	float timePerShoot;

};
