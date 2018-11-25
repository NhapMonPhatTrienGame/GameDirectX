#pragma once
#include "../EnemiesState.h"

class EnemiesAttackState :
	public EnemiesState
{
public:
	explicit EnemiesAttackState(Enemies *e);
	~EnemiesAttackState() = default;

	void update(float dt) override;
	Enemies::StateName getState() override;

protected:
	float timeAttack;
	int count;
};
